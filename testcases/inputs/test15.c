#include <stdio.h>

int a,b,c;

void foo(){
    a=c;
}

int main(){
    a = 10;
    b = 20;
    foo();
    foo();
    return 0;
}