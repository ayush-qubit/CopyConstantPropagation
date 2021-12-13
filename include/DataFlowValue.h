#ifndef DATAFLOWVALUE_H
#define DATAFLOWVALUE_H

#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/IR/Constants.h"
#include <ostream>
#include <string>

class DataFlowValue{
    private:
    llvm::ConstantInt *Element;
    llvm::ConstantFP *FPElement;
    bool Top,Bottom;

    public:
    DataFlowValue();
    DataFlowValue(llvm::ConstantInt *);
    DataFlowValue(llvm::ConstantFP *);

    int get();
    void toBottom();
    bool isTop();
    bool isBottom();
    bool isConcrete();

    friend DataFlowValue *meet(DataFlowValue *, DataFlowValue *);
    friend llvm::raw_fd_ostream & operator << (llvm::raw_fd_ostream &,DataFlowValue&);
    friend llvm::raw_ostream & operator << (llvm::raw_ostream &,DataFlowValue&);
    friend bool operator == (DataFlowValue,DataFlowValue);
    friend bool operator != (DataFlowValue,DataFlowValue);
};

#endif