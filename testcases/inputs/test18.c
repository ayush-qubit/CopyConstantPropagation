#include <stdio.h>

int a,b;

void foo(){
    int y;
    y = 20;
    b = y;
}

int main(){
    int x = 10;
    a = x;
    b = x;
    foo();
    return 0;
}