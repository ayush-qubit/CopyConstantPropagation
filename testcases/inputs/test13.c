#include <stdio.h>
int b;

struct B{
    int c,d;
};

struct B bb;

void foo(){
    b = 100;
}
int main(){
    b = 200;
    foo();
    foo();
    bb.c = 100;
    bb.d = 200;
    printf("%d",bb.c);
    scanf("%d",&bb.d);
    return 0;
}