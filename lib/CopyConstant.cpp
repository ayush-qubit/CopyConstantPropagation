#include "CopyConstant.h"

CopyConstant::CopyConstant(bool debug) : Analysis(debug) {

}

CopyConstant::CopyConstant(bool debug, const string &fileName) : Analysis(debug, fileName) {

}

ForwardDataType CopyConstant::computeOutFromIn(llvm::Instruction &I) {
    if (isa<llvm::StoreInst>(&I)) {
        return computeOutFromIn(dyn_cast<llvm::StoreInst>(&I));
    } else if (isa<llvm::LoadInst>(&I)) {
        return computeOutFromIn(dyn_cast<llvm::LoadInst>(&I));
    } else if (isa<llvm::AllocaInst>(&I)) {
        return computeOutFromIn(dyn_cast<llvm::AllocaInst>(&I));
    } else if (isa<llvm::GetElementPtrInst>(&I)) {
        return computeOutFromIn(dyn_cast<llvm::GetElementPtrInst>(&I));
    } else if (isa<llvm::PHINode>(&I)) {
        return computeOutFromIn(dyn_cast<llvm::PHINode>(&I));
    }
    return getForwardComponentAtInOfThisInstruction(I);
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::AllocaInst *I) {
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::StoreInst *I) {
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    llvm::Value *Left = I->getOperand(1);
    llvm::Value *Right = I->getValueOperand();
    if (llvm::ConstantInt *ConstInt = dyn_cast<llvm::ConstantInt>(Right)) {
        DataFlowValues[Left] = new DataFlowValue(ConstInt);
    } else if (llvm::ConstantFP *Constfp = dyn_cast<llvm::ConstantFP>(Right)) {
        DataFlowValues[Left] = new DataFlowValue(Constfp);
    } else {
        auto result = DataFlowValues.find(Right);
        if(result == DataFlowValues.end()) {
            return DataFlowValues;
        }
        DataFlowValues[Left] = result->second;
    }
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::LoadInst *I) {
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    llvm::Value *Right = I->getOperand(0);
    llvm::Value *Left = dyn_cast<llvm::Value>(I);
    auto result = DataFlowValues.find(Right);
    if(result == DataFlowValues.end()) {
        return DataFlowValues;
    }
    DataFlowValues[Left] = result->second;
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::GetElementPtrInst *I) {
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::PHINode *I) {
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    DataFlowValue *OP1DataFlowValues = NULL, *OP2DataFlowValues = NULL;
    llvm::Value *Left = dyn_cast<llvm::Value>(I);
    llvm::Value *OP1 = I->getOperand(0);
    llvm::Value *OP2 = I->getOperand(1);
    if (llvm::ConstantInt *constInt = dyn_cast<llvm::ConstantInt>(OP1)) {
        OP1DataFlowValues = new DataFlowValue(constInt);
    } else if (llvm::ConstantFP *constFP = dyn_cast<llvm::ConstantFP>(OP1)) {
        OP1DataFlowValues = new DataFlowValue(constFP);
    } else {
        auto result = DataFlowValues.find(OP1);
        if(result != DataFlowValues.end()) {
            OP1DataFlowValues = result->second;
        }
    }

    if (llvm::ConstantInt *constInt = dyn_cast<llvm::ConstantInt>(OP2)) {
        OP2DataFlowValues = new DataFlowValue(constInt);
    } else if (llvm::ConstantFP *constFP = dyn_cast<llvm::ConstantFP>(OP2)) {
        OP2DataFlowValues = new DataFlowValue(constFP);
    } else {
        auto result = DataFlowValues.find(OP2);
        if(result != DataFlowValues.end()) {
            OP2DataFlowValues = result->second;
        }
    }
    if(not (OP1DataFlowValues && OP2DataFlowValues)){
        return DataFlowValues;
    }
    DataFlowValues[Left] = meet(OP1DataFlowValues, OP2DataFlowValues);
//    if(not (OP1DataFlowValues || OP2DataFlowValues)){
//        return DataFlowValues;
//    } else if(not OP1DataFlowValues){
//        DataFlowValues[Left] = OP2DataFlowValues;
//    } else if(not OP2DataFlowValues){
//        DataFlowValues[Left] = OP1DataFlowValues;
//    } else{
//        DataFlowValues[Left] = meet(OP1DataFlowValues, OP2DataFlowValues);
//    }
    return DataFlowValues;
}

ForwardDataType CopyConstant::performMeetForward(const ForwardDataType& dfv1, const ForwardDataType& dfv2) const {
    ForwardDataType DataFlowValues;
    DataFlowValues = dfv1;
    for (auto& p : dfv2) {
        auto result = dfv1.find(p.first);
        if(result == dfv1.end()){
            DataFlowValues[p.first] = p.second;
        } else{
            DataFlowValues[p.first] = meet(result->second, p.second);
        }
    }
    return DataFlowValues;
}

std::pair<ForwardDataType, NoAnalysisType>
CopyConstant::CallInflowFunction(int label, llvm::Function *F, llvm::BasicBlock *BB, const ForwardDataType& a1,
                                 const NoAnalysisType& d1) {
    ForwardDataType Dataflowvalues;
    Dataflowvalues = getPurelyGlobalComponentForward(a1);
    return make_pair(Dataflowvalues, d1);
}

std::pair<ForwardDataType, NoAnalysisType>
CopyConstant::CallOutflowFunction(int label, llvm::Function *F, llvm::BasicBlock *BB, const ForwardDataType& a3,
                                  const NoAnalysisType& d3, const ForwardDataType& a1, const NoAnalysisType& d1) {
    ForwardDataType Dataflowvalues;
    Dataflowvalues = getPurelyGlobalComponentForward(a3);
    return make_pair(Dataflowvalues, d3);
}

ForwardDataType CopyConstant::getBoundaryInformationForward() {
    ForwardDataType DataFlowValues;
    llvm::Module *M = getCurrentModule();
    for(auto &G : M->getGlobalList()){
        if(llvm::Value *Var = dyn_cast<Value>(&G)){
            if(G.getValueType()->isIntegerTy() || G.getValueType()->isDoubleTy() || G.getValueType()->isFloatTy()){
                GlobalVariables.insert(Var);
                DataFlowValues[Var] = new DataFlowValue();
            }
        }
    }
    return DataFlowValues;
}

ForwardDataType CopyConstant::getInitialisationValueForward() {
    ForwardDataType DataFlowValues;
    llvm::Module *M = getCurrentModule();
    for(auto &G : M->getGlobalList()){
        if(llvm::Value *Var = dyn_cast<Value>(&G)){
            if(G.getValueType()->isIntegerTy() || G.getValueType()->isDoubleTy() || G.getValueType()->isFloatTy()){
                DataFlowValues[Var] = new DataFlowValue();
            }
        }
    }
    return DataFlowValues;
}

bool CopyConstant::EqualDataFlowValuesForward(const ForwardDataType &dfv1, const ForwardDataType &dfv2) const {
    if(dfv1.empty() && dfv2.empty()){
        return true;
    } else if(dfv1.empty()){
        return false;
    } else if(dfv2.empty()){
        return false;
    }
    for (auto &p : dfv1) {
        // REFER Commit: 06796bc277aa713ba5f25fed36cbe0c2b6248c04
        // TODO: Verify whether the below code is equivalent to `if (*dfv2[p.first] != *dfv1[p.first]) return false;`
        // NOTE: The condition in the above `if` block can create issues if `dfv2.find(p.first) == dfv2.end()`
        //       Because, in that case, `dfv2[p.first]` will be equal to `nullptr`

        auto a = dfv2.find(p.first);
        // Part 1 of the `if` condition: true => p.first has an entry in `dfv1` but not in `dfv2`
        // Part 2 of the `if` condition: check for equality of dereference of value pointed by p.first
        if (a == dfv2.end() || *(a->second) != *(p.second)) {
            return false;
        }
    }
    return true;
}

ForwardDataType CopyConstant::getPurelyGlobalComponentForward(const ForwardDataType& dfv) const {
    ForwardDataType DataFlowValues;
    for (auto& p : dfv) {
        if(llvm::isa<llvm::GlobalValue>(p.first)){
            DataFlowValues[p.first] = p.second;
        }
    }
    return DataFlowValues;
}

ForwardDataType CopyConstant::getPurelyLocalComponentForward(const ForwardDataType &dfv) const {
    ForwardDataType DataFlowValues;
    for (auto& p : dfv) {
        if(not llvm::isa<llvm::GlobalValue>(p.first)){
            DataFlowValues[p.first] = p.second;
        }
    }
    return DataFlowValues;
}

void CopyConstant::printDataFlowValuesForward(const ForwardDataType &dfv) const {
    for (auto& p : dfv) {
        llvm::outs() << "(";
        llvm::outs() << p.first->getName() << "=" << *p.second;
        llvm::outs() << ")";
        llvm::outs() << ",";
    }
    llvm::outs() << "\n";
}

void CopyConstant::findGlobalVariables(llvm::Instruction *I) {
    for (llvm::Value *ValOp : I->operands()) {
        if (isa<llvm::GlobalValue>(ValOp)) {
            GlobalVariables.insert(ValOp);
        }
    }
}

llvm::CallInst *CopyConstant::getCallInstruction(llvm::BasicBlock *BB) {
    for (llvm::Instruction &I : *BB) {
        if (isa<llvm::CallInst>(&I)) {
            return dyn_cast<llvm::CallInst>(&I);
        }
    }
    return nullptr;
}

int CopyConstant::GlobalVariableCount() {
    return this->GlobalVariables.size();
}