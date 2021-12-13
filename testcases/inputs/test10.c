#include <stdio.h>

int a,b;

void foo1();
void foo2();

int main(){
    a=10;
    b=20;
    foo1();
    b=30;
    foo1();
}

void foo1(){
    a=100;
    foo2();
    b=200;
}

void foo2(){
    a=1000;
    foo1();
    b=2000;
}