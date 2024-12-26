#pragma once

// C++ headers
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <random>

// C++ namespace
using namespace std;

// Function prototypes
void Variables();
void MathOperations();
void DevideOperations();
void LogicalOperations();
void CallAllFunctionsVariables();

/*
There are two types of variables: local and global.
Variables can also be constant or not.
There are three types of constants: const, constexpr, and #define.
Additionally, variables can be static, extern, and volatile.
*/

// Global variables
int global_max; // Renamed to avoid conflict

// Methods

// Lesson 1: Variables
void Variables()
{
    int a = 10; // local variable
    const int c = 10; // constant variable
    constexpr int d = 10; // constant variable - it can be calculated in compile time
    static int b = 10; // static variable
    extern int min;
    volatile int e = 10; // volatile variable - it can be changed by the system

    cout << "Local variable a is equal: " << a << '\n';
    cout << "Global variable max is equal: " << global_max << '\n'; // Updated variable name
    cout << "Global variable min is equal: " << min << '\n';
    cout << "Constant variable c is equal: " << c << '\n';
    cout << "Constant variable d is equal: " << d << '\n';
    cout << "Static variable b is equal: " << b << '\n';
    cout << "Volatile variable e is equal: " << e << '\n';
}

// Lesson 2: Math Operations
void MathOperations()
{
    int num = rand() % 10; // [b-a+1]+a - formula to set the range of numbers [a; b]

    num = num + 1;
    num += 1;
    num = num * 1;
    num *= 1;
    num = num / 1;
    num /= 1;
    num = num - 1;
    num -= 1;

    cout<< "Num is equal: " << num << '\n';

    cout << "The module of (-10) is equal = " << std::abs(-10) << '\n';
    cout << "The module of (-10.0) is equal " << std::fabs(-10.0) << '\n';
    cout << "The sqrt of 100 is equal " << std::sqrt(100) << '\n';
    cout << "The cbrt of 1000 is equal " << std::cbrt(1000) << '\n';
    cout << "The log of 2 grades is equal " << std::log(2) << '\n';
    cout << "The 2 into 3 is equal " << std::pow(2, 3) << '\n';
}

// Lesson 3: Devide Operations
void DevideOperations()
{
    constexpr int a = 10;
    constexpr int b = 3;
    constexpr float c = b;

    cout << "a/b=" << a / b << "\n";
    cout << "a/b=" << static_cast<float>(a) / b << "\n";
    cout << "a/b=" << a / c << "\n";
}

// Lesson 4: Logical Operations
void LogicalOperations()
{
    constexpr int a = 100;
    constexpr int b = 33;
    constexpr int c = 22;
    constexpr int odd_nums = (a % 2) + (b % 2) + (c % 2); // 1 - odd, 0 - even
    constexpr int even_nums = 3 - ((a % 2) + (b % 2) + (c % 2));
    constexpr int positive_nums = (a > 0) + (b > 0) + (c > 0);
    constexpr int negative_nums = (a < 0) + (b < 0) + (c < 0);

    cout << "The amount of odd numbers is equal " << odd_nums << '\n';
    cout << "The amount of even numbers is equal " << even_nums << '\n';
    cout << "The amount of positive numbers is equal " << positive_nums << '\n';
    cout << "The amount of negative numbers is equal " << negative_nums << '\n';
}

// Call all functions in sequence
void CallAllFunctionsVariables()
{
    Variables();
    MathOperations();
    DevideOperations();
    LogicalOperations();
}

// Nums out of seeing
int min = 32;
