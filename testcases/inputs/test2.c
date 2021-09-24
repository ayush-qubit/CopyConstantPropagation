#include <stdio.h>

int a,b;

void foo(){
	a=b;
}

int main(){
	a=10;
	foo();
	b=20;
	foo();
}