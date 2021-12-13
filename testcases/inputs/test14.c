#include <stdio.h>

int a,b;

struct B{
    int c;
};

void foo(){
    a = 100;
    b = 200;
}

int main(){
    a = 20;
    b = 30;
    a = a+b;
    struct B bb;
    bb.c = 900;
    foo();
    printf("%d",bb.c);
    return 0;
}