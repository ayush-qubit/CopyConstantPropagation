#include <stdio.h>

int a;

void foo(){
    //1. a = 10 || 2. a = 200
    a=200;
    //1. a = 200 || 2. a = 200
    foo();
    //1. a=100 || 2. a = TOP
    a = 100;
    //1. a=100 || 2. a = 100
}

int main(){
    a = 10;
    //0. a = 10
    foo();
    //0. a=100
    return 0;
}