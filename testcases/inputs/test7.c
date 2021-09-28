#include <stdio.h>

int a,b;

void foo(int x,int y){
    a = x;
    b = y;
}

int main(){
    int x = 10;
    int y = 20;
    foo(10,20);
    foo(10,20);
    foo(20,10);
}