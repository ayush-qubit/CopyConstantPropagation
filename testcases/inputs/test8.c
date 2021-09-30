#include <stdio.h>

int a,b;

void foo(){
    a = 100;
    b = 200;
    foo();
    b = 1000;
}
int main(){
    int x = 200;
    a = 10;
    b = x;
    x = 90;
    foo();
    b = x;
}