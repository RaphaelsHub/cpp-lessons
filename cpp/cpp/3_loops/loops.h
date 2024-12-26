#pragma once

#include <iostream>

using namespace std;

// Lesson 1: Infinite loop until a specific character is entered
void WaitForCharacterA()
{
    const char a = 'a';
    char b = '\0';
    for (;;)
    {
        cout << "Enter a char: ";
        cin >> b;
        if (a == b)
            break;
    }
}

// Lesson 2: For loop with multiple variables
void CountdownWithSquare()
{
    int x, y;
    for (x = 100, y = 1; x != 10 && y < 19; x -= 5, y++)
        std::cout << "The " << y << " num is " << x << ", it's square is " << x * x << '\n';
}

// Lesson 3: Simple while loop increment
void IncrementWhileLoop()
{
    int z = 1;
    while (z <= 10)
        z++;
}

// Lesson 4: Infinite while loop with break
void DecrementWithBreak()
{
    while (true)
    {
        static int x = 10;
        if (x == 3)
            break;
        x--;
    }
}

// Lesson 5: Summing digits of a number
void SumDigits()
{
    int suma = 0, a = 265;
    int sum = a / 100 + a / 10 % 10 + a % 10; // 13

    while (a > 0)
    {
        suma += a % 10;
        a /= 10;
    }
}

// Lesson 6: Using goto statement
void GotoExample()
{
    int y = 10;
    if (y == 10)
        goto metka;
    metka:
        y--;
}

// Lesson 7: Dynamic allocation and input
void DynamicInput()
{
    char* str = new char[10];

    cout << "Enter a string: ";
    cin >> str;
}

// Lesson 8: Menu with do-while loop and switch statement
void MenuExample()
{
    int ch;
    
    std::cout << "Press 1 to work\n";
    std::cout << "Press 2 to save\n";
    std::cout << "Press 3 to clear\n";
    std::cout << "Press 4 to exit\n";

    do {
        std::cout << "\tChoose an option: ";
        std::cin >> ch;

        switch (ch) {
        case 1:
            std::cout << "You want to work" << '\n';
            break;
        case 2:
            std::cout << "You want to save" << '\n';
            break;
        case 3:
            std::cout << "You want to clear" << '\n';
            break;
        case 4:
            std::cout << "You want to exit" << '\n';
            return;
        default:
            std::cout << "Invalid option. Please choose again." << '\n';
        }
    } while (ch > 4 || ch < 1);
}

// Lesson 9: Do-while loop until a specific number is entered
void WaitForNumberThree()
{
    int b = 0;
    do
    {
        cout << "Enter an int number: ";
        cin >> b;
    }
    while (b != 3);
}

// Call all functions in sequence
int CallAllFunctionsLoops()
{
    WaitForCharacterA();
    CountdownWithSquare();
    IncrementWhileLoop();
    DecrementWithBreak();
    SumDigits();
    GotoExample();
    DynamicInput();
    MenuExample();
    WaitForNumberThree();
    return 0;
}
