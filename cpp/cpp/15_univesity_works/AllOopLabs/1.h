// ReSharper disable CppClangTidyCertFlp30C
#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>

float a = 0, b = 0, c = 0, xs = 0, delta = 0, xe = 0, x = 0, y = 0;

void calculate_series()
{
    std::cin >> a >> b >> c >> xs >> xe >> delta;
    x = xs;

    for (; x <= xe; x += delta)
    {
        if (x < 0 && b != 0)
            y = a * std::pow((x + c), 2) - b;
        else if (x > 0 && b == 0)
        {
            y = 0.00;
            if (c != 0)
                y = (x - a) / c;
        }
        else
        {
            y = 0.00;
            if (c != 0)
                y = a + (x / c);
        }

        std::cout << "The result: " << std::fixed << std::setprecision(2) << y << std::endl;
    }
}

// Это не функция main(), но я оставлю ее для тестирования кода.
// В вашем коде должна быть функция main(), чтобы программа запускалась.
// int main() {
//     calculate_series();
//     return 0;
// }
