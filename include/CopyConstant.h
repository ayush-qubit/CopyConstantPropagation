#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "vasco/Analysis.h"
#include <vector>
#include <map>
#include <string>

typedef std::map<llvm::Value *,std::string> ForwardDataType;

class CopyConstant : public Analysis<ForwardDataType,NoAnalysisType>{
    private:
    // ForwardDataType DataFlowValues;
    std::string Bottom,Top;
    map<llvm::Value *,bool> GlobalVariables;
    // ForwardDataType InitializedVariables;
    public:
    CopyConstant(){
        Bottom = "\u22A5";
        Top = "\u22A4";
    }
    ForwardDataType computeOutFromIn(llvm::Instruction &) override;
    ForwardDataType getBoundaryInformationForward() override;
    ForwardDataType getInitialisationValueForward() override;
    ForwardDataType performMeetForward(ForwardDataType, ForwardDataType ) override;
    bool EqualDataFlowValuesForward(ForwardDataType, ForwardDataType) override;
    ForwardDataType getPurelyGlobalComponentForward(ForwardDataType) override;

    std::pair<ForwardDataType,NoAnalysisType> CallInflowFunction(int, llvm::Function*, llvm::BasicBlock*,ForwardDataType,NoAnalysisType) override;
    std::pair<ForwardDataType,NoAnalysisType> CallOutflowFunction(int, llvm::Function*, llvm::BasicBlock*, ForwardDataType, NoAnalysisType, ForwardDataType, NoAnalysisType) override;
    
    void printDataFlowValuesForward(ForwardDataType) override;

    // ForwardDataType computeOutFromIn(llvm::AllocaInst *);
    ForwardDataType computeOutFromIn(llvm::StoreInst *);
    ForwardDataType computeOutFromIn(llvm::LoadInst *);

    void findGlobalVariables(llvm::Instruction*);
    string meet(string, string);
};