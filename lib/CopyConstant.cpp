#include "CopyConstant.h"


CopyConstant::CopyConstant(bool debug) : Analysis(debug) {

}

CopyConstant::CopyConstant(bool debug,string fileName) : Analysis(debug,fileName) {

}


ForwardDataType CopyConstant::computeOutFromIn(llvm::Instruction &I) {
    findGlobalVariables(&I);
    if(isa<llvm::StoreInst>(&I)){
        return computeOutFromIn(dyn_cast<llvm::StoreInst>(&I));
    } else if(isa<llvm::LoadInst>(&I)){
        return computeOutFromIn(dyn_cast<llvm::LoadInst>(&I));
    } else if(isa<llvm::AllocaInst>(&I)){
        return computeOutFromIn(dyn_cast<llvm::AllocaInst>(&I));
    } else if(isa<llvm::GetElementPtrInst>(&I)){
        return computeOutFromIn(dyn_cast<llvm::GetElementPtrInst>(&I));
    } else if(isa<llvm::PHINode>(&I)){
        return computeOutFromIn(dyn_cast<llvm::PHINode>(&I));
    }
    return getForwardComponentAtInOfThisInstruction(I);
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::AllocaInst *I){
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    llvm::Value *Left = dyn_cast<llvm::Value>(I);
    if(Left->getType()->isIntegerTy() || Left->getType()->isFloatTy() || Left->getType()->isDoubleTy()){
        DataFlowValues[Left] = new DataFlowValue();
    }
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::StoreInst *I){
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    llvm::Value *Left = I->getOperand(1);
    llvm::Value *Right = I->getValueOperand();
    if(llvm::ConstantInt *ConstInt = dyn_cast<llvm::ConstantInt>(Right)) {
        DataFlowValues[Left] = new DataFlowValue(ConstInt);
    }else if(llvm::ConstantFP *Constfp = dyn_cast<llvm::ConstantFP>(Right)){
            DataFlowValues[Left] = new DataFlowValue(Constfp);
    } else if(this->isFormalParameter(Right)){
        DataFlowValues[Left] = FormalParameterValues[Right];
    } else{
        if(DataFlowValues.find(Right) == DataFlowValues.end()){
            return DataFlowValues;
        }
        DataFlowValues[Left] = DataFlowValues[Right];
    }
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::LoadInst *I){
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    llvm::Value *Right = I->getOperand(0);
    llvm::Value *Left = dyn_cast<llvm::Value>(I);
    if(DataFlowValues.find(Right) == DataFlowValues.end()){
        if(GlobalVariables[Right]){
            DataFlowValues[Left] = new DataFlowValue();
        }
        return DataFlowValues;
    }
    DataFlowValues[Left] = DataFlowValues[Right];
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::GetElementPtrInst *I) {
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
//    llvm::Value *Left = dyn_cast<llvm::Value>(I);
//    DataFlowValues[Left] = new DataFlowValue();
    return DataFlowValues;
}

ForwardDataType CopyConstant::computeOutFromIn(llvm::PHINode *I) {
    ForwardDataType DataFlowValues = getForwardComponentAtInOfThisInstruction(*I);
    DataFlowValue *OP1DataFlowValues = NULL,*OP2DataFlowValues = NULL;
    llvm::Value *Left = dyn_cast<llvm::Value>(I);
    llvm::Value *OP1 = I->getOperand(0);
    llvm::Value *OP2 = I->getOperand(1);
    if(llvm::ConstantInt *constInt = dyn_cast<llvm::ConstantInt>(OP1)){
        OP1DataFlowValues = new DataFlowValue(constInt);
    } else if(llvm::ConstantFP *constFP = dyn_cast<llvm::ConstantFP>(OP1)){
        OP1DataFlowValues = new DataFlowValue(constFP);
    } else{
        if(DataFlowValues.find(OP1) != DataFlowValues.end()){
            OP1DataFlowValues = DataFlowValues[OP1];
        } else if(GlobalVariables[OP1]){
            OP1DataFlowValues = new DataFlowValue();
        } else{
            OP1DataFlowValues = NULL;
        }
    }

    if(llvm::ConstantInt *constInt = dyn_cast<llvm::ConstantInt>(OP2)){
        OP2DataFlowValues = new DataFlowValue(constInt);
    } else if(llvm::ConstantFP *constFP = dyn_cast<llvm::ConstantFP>(OP2)){
        OP2DataFlowValues = new DataFlowValue(constFP);
    } else{
        if(DataFlowValues.find(OP2) != DataFlowValues.end()){
            OP1DataFlowValues = DataFlowValues[OP2];
        } else if(GlobalVariables[OP2]){
            OP2DataFlowValues = new DataFlowValue();
        } else{
            OP2DataFlowValues = NULL;
        }
    }
    if(not (OP1DataFlowValues && OP2DataFlowValues)){
        return DataFlowValues;
    }
    DataFlowValues[Left] = meet(OP1DataFlowValues,OP2DataFlowValues);
    return DataFlowValues;
}

ForwardDataType CopyConstant::performMeetForward(ForwardDataType dfv1,ForwardDataType dfv2) {
    ForwardDataType DataFlowValues;
    for(auto p : dfv1){
        if(dfv2.find(p.first) != dfv2.end()){
            // DataFlowValue result = meet(dfv1[p.first],dfv2[p.first]);
            DataFlowValues[p.first] = meet(dfv1[p.first],dfv2[p.first]);
        }
        else{
            DataFlowValues[p.first] = dfv1[p.first];
        }
    }
    for(auto p : dfv2){
        if(dfv1.find(p.first) != dfv1.end()){
            // DataFlowValue result = meet(dfv1[p.first],dfv2[p.first]);
            DataFlowValues[p.first] = meet(dfv1[p.first],dfv2[p.first]);
        }
        else{
            DataFlowValues[p.first] = dfv2[p.first];
        }
    }
    return DataFlowValues;
}

std::pair<ForwardDataType,NoAnalysisType> CopyConstant::CallInflowFunction(int label, llvm::Function *F, llvm::BasicBlock *BB, ForwardDataType a1, NoAnalysisType d1) {
    // ForwardDataType ArgumentValues;
    // llvm::CallInst *CI = this->getCallInstruction(BB);
    // llvm::Function *CF = CI->getCalledFunction();
    // for(auto &arg : CF->args()){ // Formal argument
    //     if(llvm::Value *valOp = dyn_cast<llvm::Value>(&arg)){
    //         ArgumentValues[valOp] = new DataFlowValue();
    //     }
    // }
    // int index = 0;
    // for(auto &p : ArgumentValues){
    //     llvm::Value *valOp = CI->getArgOperand(index);
    //     if(llvm::ConstantInt *Const = dyn_cast<llvm::ConstantInt>(valOp)){
    //         p.second = new DataFlowValue(Const);
    //     }
    //     index++;
    // }
    // for(auto p : ArgumentValues){
    //     FormalParameterValues[p.first] = p.second;
    // }
//    outs() << "\n";
//    outs() << "CALLINFLOW CALLED" << "\n";
//    printDataFlowValuesForward(a1);
    a1 = getPurelyGlobalComponentForward(a1);
//    outs() << "\n";
    return make_pair(a1,d1);
}

std::pair<ForwardDataType,NoAnalysisType> CopyConstant::CallOutflowFunction(int label, llvm::Function *F, llvm::BasicBlock *BB, ForwardDataType a3, NoAnalysisType d3, ForwardDataType a1, NoAnalysisType d1){
    a3 = getPurelyGlobalComponentForward(a3);
    return make_pair(a3,d3);
}

ForwardDataType CopyConstant::getBoundaryInformationForward() {
    ForwardDataType DataFlowValues;
    llvm::Module *M = getCurrentModule();
    for(auto &G : M->getGlobalList()){
        if(llvm::Value *Var = dyn_cast<Value>(&G)){
            if(G.getValueType()->isIntegerTy() || G.getValueType()->isDoubleTy() || G.getValueType()->isFloatTy()){
                GlobalVariables[Var] = true;
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

bool CopyConstant::EqualDataFlowValuesForward(ForwardDataType dfv1, ForwardDataType dfv2) {
    for(auto p : dfv1){
        if(dfv2.find(p.first) == dfv2.end()){
            return false;
        }
        else if(*dfv1[p.first] != *dfv2[p.first]){
            return false;
        }
    }
    for(auto p : dfv2){
        if(dfv1.find(p.first) == dfv1.end()){
            return false;
        }
        else if(*dfv1[p.first] != *dfv2[p.first]){
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
    for(auto p : dfv){
        outs() << "(";
        outs() << p.first->getName() << "=" << *p.second;
        outs() << ")";
        outs() << ",";
    }
    outs() << "\n";
}

void CopyConstant::findGlobalVariables(llvm::Instruction *I) {
//    outs() << "\nFINDING GLOBAL VARIABLES: ";
//    outs() << *I << "\n";
    for(llvm::Value *ValOp : I->operands()){
        if(isa<llvm::GlobalValue>(ValOp)){
            GlobalVariables[ValOp] = true;
//            outs() << ValOp->getName() << "\n";
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

bool CopyConstant::isFormalParameter(llvm::Value *valOp){
    return FormalParameterValues.find(valOp) != FormalParameterValues.end();
}