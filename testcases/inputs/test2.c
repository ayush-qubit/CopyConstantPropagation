#include <stdio.h>

int a,b;

void foo(){
	a=b;
}
void foo1(){
    b = a;
}
int main(){
	a=10;
    foo1();
}