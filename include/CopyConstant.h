#ifndef COPYCONSTANT_H
#define COPYCONSTANT_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/Debug.h"
#include "vasco/Analysis.h"
#include "DataFlowValue.h"
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>

typedef std::unordered_map<llvm::Value *,DataFlowValue *> ForwardDataType;

class CopyConstant : public Analysis<ForwardDataType,NoAnalysisType>{
    private:
    ForwardDataType FormalParameterValues;
    std::unordered_set<llvm::Value*> GlobalVariables;
    public:
    CopyConstant(bool);
    CopyConstant(bool,string);
    ForwardDataType computeOutFromIn(llvm::Instruction &) override;
    ForwardDataType getBoundaryInformationForward() override;
    ForwardDataType getInitialisationValueForward() override;
    ForwardDataType performMeetForward(ForwardDataType, ForwardDataType ) override;
    bool EqualDataFlowValuesForward(ForwardDataType, ForwardDataType) override;
    ForwardDataType getPurelyGlobalComponentForward(ForwardDataType) override;
    ForwardDataType getPurelyLocalComponentForward(ForwardDataType) override;

    std::pair<ForwardDataType,NoAnalysisType> CallInflowFunction(int, llvm::Function*, llvm::BasicBlock*,ForwardDataType,NoAnalysisType) override;
    std::pair<ForwardDataType,NoAnalysisType> CallOutflowFunction(int, llvm::Function*, llvm::BasicBlock*, ForwardDataType, NoAnalysisType, ForwardDataType, NoAnalysisType) override;
    
    void printDataFlowValuesForward(ForwardDataType) override;

    ForwardDataType computeOutFromIn(llvm::AllocaInst *);
    ForwardDataType computeOutFromIn(llvm::StoreInst *);
    ForwardDataType computeOutFromIn(llvm::LoadInst *);
    ForwardDataType computeOutFromIn(llvm::GetElementPtrInst *);
    ForwardDataType computeOutFromIn(llvm::PHINode *);

    void findGlobalVariables(llvm::Instruction*);
    llvm::CallInst *getCallInstruction(llvm::BasicBlock *);
    bool isFormalParameter(llvm::Value *);
    int GlobalVariableCount();
};

#endif