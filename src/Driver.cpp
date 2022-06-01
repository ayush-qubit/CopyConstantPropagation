#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Transforms/Utils/UnifyFunctionExitNodes.h"
#include "CopyConstant.h"

#include <string>
#include <iomanip>

using namespace llvm;

int main(int argc, char **argv) {
    if (argc < 1) {
        return 1;
    }
    LLVMContext Context;
    SMDiagnostic Error;
    std::unique_ptr<Module> M = parseIRFile(argv[1], Error, Context);
    legacy::FunctionPassManager FPM(M.get());
    Pass *UEN = createUnifyFunctionExitNodesPass();
    FPM.add(UEN);
    for (Function &F : M.get()->functions()) {
        FPM.run(F);
    }
    string fileName = argv[1];
    fileName += ".txt";
    CopyConstant CC(true, fileName);
    CC.doAnalysis(*M);
<<<<<<< HEAD
//    CC.printContext();
=======
     CC.printContext();
>>>>>>> testing
    outs() << "\n";
    outs() << "Total number of contexts created: " << CC.getNumberOfContexts() << "\n";
    return 0;
}