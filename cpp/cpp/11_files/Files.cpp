#include<iostream>
//#include<stdio.h>// C - io put

#include"files/Boo.h"
#include"files/Foo.h"
#include"files/Sum.h"
#include"files/SumClass.h"
#include"files/WorkingWithFiles.h"

extern "C"
{
    void my_func();
}

void my_func()
{
    printf("HelloWorld\n");
}

int main()
{
    my_func();
    std::cout << Sum(1,3)<<"\n";
    std::cout << SumClass::OtherSum(1,3)<<"\n";
    std::cout << Foo()<<"\n";
    std::cout << Boo()<<"\n";
    IOFile();
    Input10Str();
    Output10Str();
    OverLoadingIOstrem();
    
    return 0;
}
