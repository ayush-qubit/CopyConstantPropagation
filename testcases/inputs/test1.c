#include <stdio.h>

int a,b;

void foo(){
    //1.(a=Bot)(b=Top) || 2.(a=Bot)(b=Bot) || 3.(a=50)(b=100) || 4.(a=50)(b=50)
    b = a;
    //1.(a=Bot)(b=Bot) || 2.(a=Bot)(b=Bot) || 3.(a=50)(b=50) || 4.(a=50)(b=50)
    foo();
    //1.(a=Top)(b=100) || 2.(a=Top)(b=Top) || 3.(a=Top)(b=100) || 4.(a=Top)(b=Top)
    b = 100;
    //1.(a=Top)(b=100) || 2.(a=Top)(b=100) || 3.(a=Top)(b=100) || 4.(a=Top)(b=100)
}

int main(){
    int x,y;
    x = 10;
    y = x;
    x = 30;
    a = y;
    // 0.(a=10)
    if(a>40){
        a = x;
        //0.(a=30)
    }
    //0.(a=Bot)
    y = a;
    //0.(a=Bot)(b=Top)
    foo();
    //0.(a=Top)(b=100)
    a = 50;
    //0.(a=50)(b=100)
    foo();
    //0.(a=Top)(b=100)
    return 0;
    //0.(a=Top)(b=100)
}