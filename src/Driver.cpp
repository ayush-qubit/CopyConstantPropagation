#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Transforms/Utils/UnifyFunctionExitNodes.h"
#include "CopyConstant.h"
#include "chrono"

#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include <iomanip>

using namespace llvm;
using namespace std::chrono;

int main(int argc, char **argv){
    if(argc<1){
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
    CopyConstant CC(false,fileName);
    auto start = high_resolution_clock::now();
    CC.doAnalysis(*M);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    CC.printContext();
    outs() << "\n";
    outs() << "Time taken by analysis: " << duration.count() << " seconds" << "\n";
    outs() << "Total number of contexts created: " << CC.getNumberOfContexts() << "\n";
    return 0;
}