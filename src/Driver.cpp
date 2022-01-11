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

using namespace llvm;
using namespace std::chrono;

void process_mem_usage(double& vm_usage, double& resident_set)
{
    using std::ios_base;
    using std::ifstream;
    using std::string;

    vm_usage     = 0.0;
    resident_set = 0.0;

    // 'file' stat seems to give the most reliable results
    //
    ifstream stat_stream("/proc/self/stat",ios_base::in);

    // dummy vars for leading entries in stat that we don't care about
    //
    string pid, comm, state, ppid, pgrp, session, tty_nr;
    string tpgid, flags, minflt, cminflt, majflt, cmajflt;
    string utime, stime, cutime, cstime, priority, nice;
    string O, itrealvalue, starttime;

    // the two fields we want
    //
    unsigned long vsize;
    long rss;

    stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                >> utime >> stime >> cutime >> cstime >> priority >> nice
                >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

    stat_stream.close();

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage     = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}

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
    double vm, rss;
    process_mem_usage(vm, rss);
    outs() << "\n";
    outs() << "Time taken by analysis: " << duration.count() << " seconds" << "\n";
    outs() << "Total number of contexts created: " << CC.getNumberOfContexts() << "\n";
    outs() << "Context label counter: " << CC.getContextLabelCounter() << "\n";
    llvm::outs() << "Memory consume: " << vm << " KB" << "\n";
    return 0;
}