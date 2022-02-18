#include "DataFlowValue.h"

DataFlowValue::DataFlowValue(){
    this->Element = nullptr;
    this->FPElement = nullptr;
    this->Top = true;
    this->Bottom = false;
}

DataFlowValue::DataFlowValue(llvm::ConstantInt *Element){
    if(not Element){
        throw "Parameter cannot be NULL";
    }
    this->Element = Element;
    this->FPElement = nullptr;
    this->Top = false;
    this->Bottom = false;
}

DataFlowValue::DataFlowValue(llvm::ConstantFP *Element) {
    if(not Element){
        throw "Parameter cannot be NULL";
    }
    this->Element = nullptr;
    this->FPElement = Element;
    this->Top = false;
    this->Bottom = false;
}

int DataFlowValue::get(){
    if(not (this->Element || this->FPElement)){
        throw "Data flow value is not concrete";
    }
    if(this->Element){
        return this->Element->getSExtValue();
    }
    if(this->FPElement){
        return this->FPElement->getValueID();
    }
    return INT_MAX;
}

void DataFlowValue::toBottom(){
    this->Element = nullptr;
    this->FPElement = nullptr;
    this->Bottom = true;
    this->Top = false;
}

bool DataFlowValue::isTop(){
    return this->Top;
}

bool DataFlowValue::isBottom(){
    return this->Bottom;
}

bool DataFlowValue::isConcrete(){
    return not(this->isBottom() || this->isTop());
}

DataFlowValue *meet(DataFlowValue *dfv1, DataFlowValue *dfv2){
//    if(not (dfv1 || dfv2)){
//        return NULL;
//    } else if(not dfv1){
//        return dfv2;
//    } else if(not dfv2){
//        return dfv1;
//    }
    if(dfv1 == NULL || dfv2 == NULL){
        if(dfv1 == NULL){
            return dfv2;
        }
        return dfv1;
    }
    if(dfv1->isBottom() && dfv2->isBottom()){
        return dfv1;
    } else if(dfv1->isTop()){
        return dfv2;
    } else if(dfv2->isTop()){
        return dfv1;
    } else if(*dfv1 == *dfv2){
        return dfv1;
    }
    dfv1->toBottom();
    return dfv1;
}

llvm::raw_fd_ostream & operator << (llvm::raw_fd_ostream &out, DataFlowValue& dfv){
    if(dfv.isTop()){
        out << "\u22A4";
    } else if(dfv.isBottom()){
        out << "\u22A5";
    } else{
        out << dfv.get();
    }
    return out;
}

llvm::raw_ostream & operator << (llvm::raw_ostream &out, DataFlowValue& dfv){
    if(dfv.isTop()){
        out << "\u22A4";
    } else if(dfv.isBottom()){
        out << "\u22A5";
    } else{
        out << dfv.get();
    }
    return out;
}

bool operator == (DataFlowValue dfv1,DataFlowValue dfv2){
    if(dfv1.isTop() && dfv2.isTop()){
        return true;
    } else if(dfv1.isBottom() && dfv2.isBottom()){
        return true;
    } else if(dfv1.isConcrete() && dfv2.isConcrete()){
        if(dfv1.Element && dfv2.Element){
            return dfv1.Element == dfv2.Element;
        }
        if(dfv1.FPElement && dfv2.FPElement){
            return dfv1.FPElement == dfv2.FPElement;
        }
        return false;
    }
    return false;
}

bool operator != (DataFlowValue dfv1, DataFlowValue dfv2){
    return not(dfv1 == dfv2);
}


