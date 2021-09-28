#include "CopyConstant.h"

ForwardDataType CopyConstant::computeOutFromIn(llvm::Instruction &I) {
    findGlobalVariables(&I);
    if(isa<llvm::StoreInst>(&I)){
        return computeOutFromIn(dyn_cast<llvm::StoreInst>(&I));
    } else if(isa<llvm::LoadInst>(&I)){
        return computeOutFromIn(dyn_cast<llvm::LoadInst>(&I));
    } else if(isa<llvm::AllocaInst>(&I)){
        return computeOutFromIn(dyn_cast<llvm::AllocaInst>(&I));
    } else if(isa<llvm::GetElementPtrInst>(&I)){
        outs() << REDB << "Instruction not supported!!!!!!" << RST << "\n";
    }
    return getForwardComponentAtInOfThisInstruction(I);
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::AllocaInst *I){
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    llvm::Value *Left = dyn_cast<llvm::Value>(I);
    DataFlowValues[Left] = Top;
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::StoreInst *I){
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    llvm::Value *Left = I->getOperand(1);
    llvm::Value *Right = I->getValueOperand();
    if(llvm::ConstantInt *ConstInt = dyn_cast<llvm::ConstantInt>(Right)) {
        DataFlowValues[Left] = std::to_string(ConstInt->getSExtValue());
    } else if(this->isFormalParameter(Right)){
        DataFlowValues[Left] = FormalParameterValues[Right];
    } else{
        DataFlowValues[Left] = DataFlowValues[Right];
    }
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::LoadInst *I){
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    llvm::Value *Right = I->getOperand(0);
    llvm::Value *Left = dyn_cast<llvm::Value>(I);
    DataFlowValues[Left] = DataFlowValues[Right];
    return DataFlowValues;
}

ForwardDataType CopyConstant::performMeetForward(ForwardDataType dfv1,ForwardDataType dfv2) {
    ForwardDataType DataFlowValues;
    for(auto p : dfv1){
        if(dfv2.find(p.first) != dfv2.end()){
            // DataFlowValues[p.first] = (dfv1[p.first] == dfv2[p.first] ? dfv1[p.first] : Bottom);
            DataFlowValues[p.first] = meet(dfv1[p.first],dfv2[p.first]);
        }
        else{
            DataFlowValues[p.first] = dfv1[p.first];
        }
    }
    for(auto p : dfv2){
        if(dfv1.find(p.first) != dfv1.end()){
            // DataFlowValues[p.first] = (dfv1[p.first] == dfv2[p.first] ? dfv1[p.first] : Bottom);
            DataFlowValues[p.first] = meet(dfv1[p.first],dfv2[p.first]);
        }
        else{
            DataFlowValues[p.first] = dfv2[p.first];
        }
    }
    return DataFlowValues;
}

std::pair<ForwardDataType,NoAnalysisType> CopyConstant::CallInflowFunction(int label, llvm::Function *F, llvm::BasicBlock *BB, ForwardDataType a1, NoAnalysisType d1) {
    outs() << "\nCALLINFLOWFUNCTION CALLED!!!!!!!!!!!!" << " ";
    ForwardDataType ArgumentValues;
    llvm::CallInst *CI = this->getCallInstruction(BB);
    llvm::Function *CF = CI->getCalledFunction();
    for(auto &arg : CF->args()){ // Formal argument
        if(llvm::Value *valOp = dyn_cast<llvm::Value>(&arg)){
            ArgumentValues[valOp] = Top;
        }
    }
    int index = 0;
    for(auto &p : ArgumentValues){
        llvm::Value *valOp = CI->getArgOperand(index);
        if(llvm::ConstantInt *Const = dyn_cast<llvm::ConstantInt>(valOp)){
            p.second = std::to_string(Const->getSExtValue());
        }
        else{
            p.second = a1[valOp];
        }
        index++;
    }
    for(auto p : ArgumentValues){
        FormalParameterValues[p.first] = p.second;
    }
    a1 = getPurelyGlobalComponentForward(a1);
    return make_pair(a1,d1);
}

std::pair<ForwardDataType,NoAnalysisType> CopyConstant::CallOutflowFunction(int label, llvm::Function *F, llvm::BasicBlock *BB, ForwardDataType a3, NoAnalysisType d3, ForwardDataType a1, NoAnalysisType d1){
    a3 = getPurelyGlobalComponentForward(a3);
    return make_pair(a3,d3);
}

ForwardDataType CopyConstant::getBoundaryInformationForward() {
    ForwardDataType DataFlowValues;
    return DataFlowValues;
}

ForwardDataType CopyConstant::getInitialisationValueForward() {
    ForwardDataType DataFlowValues;
    llvm::Module *M = getCurrentModule();
    for(auto &G : M->getGlobalList()){
        if(llvm::Value *Var = dyn_cast<Value>(&G)){
            DataFlowValues[Var] = Top;
            GlobalVariables[Var] = true;
        }
    }
    return DataFlowValues;
}

bool CopyConstant::EqualDataFlowValuesForward(ForwardDataType dfv1, ForwardDataType dfv2) {
    for(auto p : dfv1){
        if(dfv2.find(p.first) == dfv2.end()){
            return false;
        }
        else if(dfv1[p.first] != dfv2[p.first]){
            // outs() << "DataFLow Values are not equal: ";
            // printDataFlowValuesForward(dfv1);
            // printDataFlowValuesForward(dfv2);
            return false;
        }
    }
    for(auto p : dfv2){
        if(dfv1.find(p.first) == dfv1.end()){
            return false;
        }
        else if(dfv1[p.first] != dfv2[p.first]){
            // outs() << "DataFLow Values are not equal: ";
            // printDataFlowValuesForward(dfv1);
            // printDataFlowValuesForward(dfv2);
            return false;
        }
    }
    return true;
}

ForwardDataType CopyConstant::getPurelyGlobalComponentForward(ForwardDataType dfv) {
    ForwardDataType DataFlowValues;
    for(auto p : dfv){
        if(GlobalVariables[p.first]){
            DataFlowValues[p.first] = p.second;
        }
    }
    return DataFlowValues;
}

ForwardDataType CopyConstant::getPurelyLocalComponentForward(ForwardDataType dfv){
    ForwardDataType DataFlowValues;
    for(auto p : dfv){
        if(not GlobalVariables[p.first]){
            DataFlowValues[p.first] = p.second;
        }
    }
    return DataFlowValues;
}

void CopyConstant::printDataFlowValuesForward(ForwardDataType dfv) {
    // outs() << "Printing Data FLow Values forward" << "\n";
    // outs() << dfv.size();
    for(auto p : dfv){
        outs() << "(";
        outs() << p.first->getName() << "=" << p.second;
        outs() << ")";
        outs() << ",";
    }
    outs() << "\n";
}

void CopyConstant::findGlobalVariables(llvm::Instruction *I) {
    for(llvm::Value *ValOp : I->operands()){
        if(isa<llvm::GlobalValue>(ValOp)){
            GlobalVariables[ValOp] = true;
            // InitializedVariables[ValOp->getName().str()] = Top;
        }
    }
}

llvm::CallInst *CopyConstant::getCallInstruction(llvm::BasicBlock *BB){
    for(llvm::Instruction &I : *BB){
        if(isa<llvm::CallInst>(&I)){
            return dyn_cast<llvm::CallInst>(&I);
        }
    }
    return nullptr;
}

string CopyConstant::meet(string val1, string val2){
    if(val1 == Bottom || val2 == Bottom){
        return Bottom;
    }
    if(val1 == Top){
        return val2;
    }
    if(val2 == Top){
        return val1;
    }
    if(val1 == val2){
        return val1;
    }
    return Bottom;
}

bool CopyConstant::isFormalParameter(llvm::Value *valOp){
    if(FormalParameterValues.find(valOp) != FormalParameterValues.end()){
        return true;
    }
    return false;
}