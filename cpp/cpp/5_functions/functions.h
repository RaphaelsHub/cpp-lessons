#pragma once

#include "iostream"

// Function to calculate Fibonacci number
int Fibonacci(int a)
{
    if (a == 0 || a == 1)
        return 1;
    return Fibonacci(a - 2) + Fibonacci(a - 1);
}

// Overloaded function to calculate Fibonacci number with an initial value
int Fibonacci(int a, int initial)
{
    if (a == 0)
        return initial;
    if (a == 1)
        return initial;
    return Fibonacci(a - 2, initial) + Fibonacci(a - 1, initial);
}

// Function to calculate factorial using recursion
int RecursionFactorial(int a)
{
    if (a == 1)
        return 1;
    const auto res = a * RecursionFactorial(a - 1);
    return res;
}

// Function to multiply two numbers using recursion
int RecursionMultiply(const int a, const int b)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    return a * (RecursionMultiply(a, b - 1));
}

// Function to calculate GCD (Greatest Common Divisor) using recursion
int RecursionGCD(const int a, const int b)
{
    if (b == 0) return a;
    return RecursionGCD(b, a % b);
}

// Inline function to add two integers
inline int Add(const int i, const int b)
{
    return i + b;
}

// Overloaded inline function to add three integers
inline int Add(const int i, const int b, const int c)
{
    return i + b + c;
}

int CallAllFunctions()
{
    constexpr int a = 4;
    constexpr int b = 3;

    // Calculate and print Fibonacci of a
    std::cout << "Fibonacci of " << a << " is: " << Fibonacci(a) << '\n';
    std::cout << "Overloaded Fibonacci of " << a << " with initial 2 is: " << Fibonacci(a, 2) << '\n';

    // Calculate and print factorial of a
    std::cout << "Factorial of " << a << " is: " << RecursionFactorial(a) << '\n';

    // Multiply a and b using recursion and print result
    std::cout << a << " multiplied by " << b << " is: " << RecursionMultiply(a, b) << '\n';

    // Calculate and print GCD of a and b
    std::cout << "GCD of " << a << " and " << b << " is: " << RecursionGCD(a, b) << '\n';

    // Add a and b using inline function and print result
    const int sumTwo = Add(a, b);
    std::cout << "Sum of " << a << " and " << b << " is: " << sumTwo << '\n';

    // Add a, b, and 2 using overloaded inline function and print result
    const int sumThree = Add(a, b, 2);
    std::cout << "Sum of " << a << " and " << b << " and 2 is: " << sumThree << '\n';

    return 0;
}
