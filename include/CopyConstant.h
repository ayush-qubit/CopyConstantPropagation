#ifndef COPYCONSTANT_H
#define COPYCONSTANT_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/Debug.h"
#include "Analysis.h"
#include "DataFlowValue.h"
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>

typedef std::unordered_map<llvm::Value *,DataFlowValue *> ForwardDataType;

class CopyConstant : public Analysis<ForwardDataType,NoAnalysisType>{
    private:
    std::unordered_set<llvm::Value*> GlobalVariables;
    public:
    explicit CopyConstant(bool);
    CopyConstant(bool, const string &);
    ForwardDataType computeOutFromIn(llvm::Instruction &) override;
    ForwardDataType getBoundaryInformationForward() override;
    ForwardDataType getInitialisationValueForward() override;
    ForwardDataType performMeetForward(const ForwardDataType &, const ForwardDataType & ) const override;
    bool EqualDataFlowValuesForward(const ForwardDataType&, const ForwardDataType&) const override;
    ForwardDataType getPurelyGlobalComponentForward(const ForwardDataType &) const override;
    ForwardDataType getPurelyLocalComponentForward(const ForwardDataType&) const override;

    std::pair<ForwardDataType,NoAnalysisType> CallInflowFunction(int, llvm::Function*, llvm::BasicBlock*,const ForwardDataType &,const NoAnalysisType &) override;
    std::pair<ForwardDataType,NoAnalysisType> CallOutflowFunction(int, llvm::Function*, llvm::BasicBlock*, const ForwardDataType &, const NoAnalysisType &, const ForwardDataType &, const NoAnalysisType &) override;

    void printDataFlowValuesForward(const ForwardDataType&) const override;

    ForwardDataType computeOutFromIn(llvm::AllocaInst *);
    ForwardDataType computeOutFromIn(llvm::StoreInst *);
    ForwardDataType computeOutFromIn(llvm::LoadInst *);
    ForwardDataType computeOutFromIn(llvm::GetElementPtrInst *);
    ForwardDataType computeOutFromIn(llvm::PHINode *);

    void findGlobalVariables(llvm::Instruction*);
    llvm::CallInst *getCallInstruction(llvm::BasicBlock *);
    int GlobalVariableCount();
};

#endif