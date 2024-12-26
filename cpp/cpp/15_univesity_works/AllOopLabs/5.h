#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>

typedef struct
{
    char str[51]; // 50 символов + завершающий нуль
} strings;

strings *tmp;

void swap(int x, int y, strings *Var[])
{
    tmp = Var[x];
    Var[x] = Var[y];
    Var[y] = tmp;
}

void processArray()
{
    strings *array[10] = {};

    for (int i = 0; i < 10; i++)
    {
        array[i] = (strings*)malloc(sizeof(strings));
        std::cin >> array[i]->str;
    }

    for (int x = 0; x < 10; x++)
    {
        for (int y = x + 1; y < 10; y++)
        {
            if (array[x]->str[0] == array[y]->str[0])
                for (int i = 0; array[x]->str[i]; i++)
                    if (array[x]->str[i] < array[y]->str[i])
                        swap(x, y, array);
            if (array[x]->str[0] < array[y]->str[0])
                swap(x, y, array);
        }
    }

    for (int i = 0; i < 10; i++)
        std::cout << array[i]->str << " ";
}

// Это не функция main(), но я оставлю ее для тестирования кода.
// В вашем коде должна быть функция main(), чтобы программа запускалась.
// int main() {
//     processArray();
//     return 0;
// }
