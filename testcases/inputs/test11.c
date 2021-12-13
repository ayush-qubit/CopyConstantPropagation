#include "stdio.h"
float a=1.56;

void foo(){
    a = 10.5f;
}
int main(){
    a = 10.9f;
    foo();
    return 0;
}