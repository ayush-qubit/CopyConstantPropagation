#include <stdio.h>

int a,b;

void foo(){
	a = b;
}

int main(){
	a = 10;
	{
		int a;
		a = 100;
		b = a;
	}
	foo();
	return 0;
}