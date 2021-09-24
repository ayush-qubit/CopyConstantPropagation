#include <stdio.h>

int a,b;

void foo(){
	a = b;
}

int main(){
	int x = 900;
	a = x;
	{
		int x;
		x = 100;
		b = x;
	}
	foo();
	return 0;
}