#include <stdio.h>

int a,b;

void foo1(){
    a = 10;
    b = 20;
}

void foo2(int x,int y){
    b = y;
    a = x;
}

int main(){
    int x,y;
    x = 100;
    y = 200;
    foo1();
    // foo2(20,10);
    a = x;
    b = y;
}