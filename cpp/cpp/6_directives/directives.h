#pragma once

#include <iostream>

// Define FUNCTION(a) if not defined
#ifndef FUNCTION
#define FUNCTION(a) ((a) < 0 ? -(a) : (a))
#endif

// Define LEFT if not defined
#ifndef LEFT
#define LEFT 1
#endif

// Define RIGHT if not defined
#ifndef RIGHT
#define RIGHT (LEFT + LEFT)
#endif

// Define TEXT if not defined
#ifndef TEXT
#define TEXT "My name is Ralph\n"
#endif

/*
 * Preprocessors are a set of instructions that regulate the compiler's work. These instructions are called preprocessor directives.
 * #define LEFT 1
 *
 * Conditional compilation directives - #elif #if #else #endif - These directives allow you to choose the parts of the program to be compiled depending on the value of a constant expression.
 *
 * #ifdef #ifndef - If the macro is defined, if the macro is not defined
 *
 * #undef - Delete the defined constant value
 *
 * #line sets the line counter
 */
using namespace std;

int CheckHowDirectivesWork()
{
    // Output predefined constants
    cout << LEFT << " " << RIGHT << " \n" << TEXT; 
    cout << (FUNCTION(10)) << '\n';

    // Conditional compilation example
#if RIGHT > 5
    cout << "More than 5\n";
#elif RIGHT == 2
    cout << "Equal to 2\n";
#else
    cout << "Less than 5\n";
#endif

    // Checking if macro LEFT is defined
#ifdef LEFT
    cout << "Defined\n";
#else
    cout << "Not defined\n";
#endif

    // Checking if macro RALPH is not defined
#ifndef RALPH
    cout << "Not defined\n";
#endif

    return 0;
}
