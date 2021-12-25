#include <stdio.h>

int a,b;


void foo(){
    a = 100;
    b = 200;
}

int main(){
    foo();
    a = 10;
    b = 20;
    void (*fp)(void) = &foo;
    fp();
    return 0;
}