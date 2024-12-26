#pragma once

#include <iostream>
#include <memory>
#include <string>

/*
data_type *pointerName;
There are two ways to use a pointer:
1. Without the * symbol - the actual memory address where the pointer points to
2. With the * symbol - the value stored in the memory
Operations for working with pointers in C:
1. The * (asterisk) operator - allows you to get the value of an object by its address - determines the value of a variable contained at the address stored in the pointer
2. The & (ampersand) operator - allows you to determine the address of a variable.
char c; - variable
char *p; - pointer
p = &c; - p = address of c
*/

// Function to demonstrate pointer usage
inline auto GetValue()
{
    int x = 0;
    int* pX = &x;
    int** pXy = &pX;
    x = **pXy;
    
    return *pX;
}

// Class definition with constructor and destructor
class MyClass
{
private:
    int value_;

public:
    MyClass(int a) { value_ = a; }
    ~MyClass() = default;
};

// Function to demonstrate smart pointer usage
inline void MakePointer()
{
    std::auto_ptr<MyClass> autoPtr(new MyClass(1));
    // Using auto_ptr (obsolete, not recommended)

    std::unique_ptr<MyClass> uniquePtr(new MyClass(2));
    // Using unique_ptr (used for unique ownership of resource)

    std::shared_ptr<MyClass> sharedPtr1(new MyClass(3));
    // Using shared_ptr (used for shared ownership of resource)

    std::shared_ptr<MyClass> sharedPtr2 = sharedPtr1;
    // Creating a second shared_ptr that also references the same object

    // Using auto to create a smart pointer (should be convenient)
    auto autoPtr1 = std::make_shared<MyClass>(4);
    auto autoPtr2 = autoPtr1;

    // Using unique_ptr smart pointer (should be convenient)
    auto uniqueShared = std::make_unique<MyClass>(5);
}

// Function declarations for different data sources
inline std::string GetDataFromBD() { return "BD"; }
inline std::string GetDataFromCEO() { return "CEO"; }
inline std::string GetDataFromCustomer() { return "CUSTOMER"; }

// Function to display data using a function pointer
inline void ShowData(std::string (*Data)())
{
    std::cout << Data() << "\n";
}

void CallAllPointerFunctions()
{
    // Getting and printing value using pointers
    std::cout << GetValue() << "\n";

    // Showing data from customer using function pointer
    ShowData(GetDataFromCustomer);

    // Assigning function to a function pointer and showing data
    std::string (*Data)() = GetDataFromBD;
    ShowData(Data);

    // Demonstrating smart pointer usage
    MakePointer();
}
