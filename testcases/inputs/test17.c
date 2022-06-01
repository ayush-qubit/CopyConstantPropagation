#include <stdio.h>

int a,b;

void foo(){
    // 1. a=10,b=TOP , 2. a=1000,b=top
    a = 1000;
    b = a+1;
    if(b<=a){
        // 1. a = 1000,b=top 2. a=1000,b=top
        foo();
        // 2. a=top,b=top
    }
    // 2.
    b = 200;
    a = b+1;
}

int main(){
    int x;
    x = 10;
    a = x;
    if(a<b){
        //0. a=10,b=TOP
        foo();
    }
    x++;
    a = x;
    return 0;
}