#ifndef COPYCONSTANT_H
#define COPYCONSTANT_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "vasco/Analysis.h"
#include "DataFlowValue.h"
#include <map>
#include <string>

#define REDB "\033[1;91m"
#define RST "\033[0;m"

typedef std::map<llvm::Value *,DataFlowValue *> ForwardDataType;

class CopyConstant : public Analysis<ForwardDataType,NoAnalysisType>{
    private:
    ForwardDataType FormalParameterValues;
    map<llvm::Value *,bool> GlobalVariables;
    public:
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

    void findGlobalVariables(llvm::Instruction*);
    llvm::CallInst *getCallInstruction(llvm::BasicBlock *);
    bool isFormalParameter(llvm::Value *);
};

#endif