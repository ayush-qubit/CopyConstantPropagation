#include <stdio.h>

int a;
struct A{
    int b;
};

int main(){
    int x,y;
    struct A aa;
    x = 10;
    y = 20;
    aa.b = x;
    a = aa.b;
    return a;
}