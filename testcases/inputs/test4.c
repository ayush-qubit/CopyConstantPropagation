#include <stdio.h>

int a,b;

void foo(){
	int x = 10;
	a = x;
	a = b;
}

int main(){
	int x = 900;
	a = x;
	{
		int x;
		x = 100;
		b = x;
		a = x;
	}
	a = x;
	foo();
	return 0;
}