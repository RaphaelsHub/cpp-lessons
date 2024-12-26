#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

size_t isThere(short int *array, int index)
{
    for (size_t i = index; i < 10; i++)
        if (array[i] % 2 == 0 && array[i] != 0)
            return i;
    return 0;
}

void processArray()
{
    std::srand(std::time(nullptr));
    short int array[10];
    short int max = -30000, min = 30000;

    for (size_t i = 0; i < 10; i++)
    {
        array[i] = std::rand() % 101;                 // Инициализация
        std::cout << array[i] << " ";                 // Мгновенный вывод
        max = (max < array[i]) ? array[i] : max; // Сравнение и поиск максимального
        min = (min > array[i]) ? array[i] : min; // Сравнение и поиск минимального
    }

    std::cout << "\nThe max num is " << max << ".\nThe min num is " << min << ".\n";

    for (size_t i = 0; i < 10; i++)
        if ((array[i] == 0 || array[i] % 2))
        {
            size_t isThereOddNum = isThere(array, i + 1);
            if (isThereOddNum != 0)
            {
                array[i] = array[isThereOddNum];
                array[isThereOddNum] = 0;
            }
            else
                array[i] = 0;
        }

    for (size_t i = 0; i < 10; i++)
        std::cout << array[i] << " ";
}

// Это не функция main(), но я оставлю ее для тестирования кода.
// В вашем коде должна быть функция main(), чтобы программа запускалась.
// int main() {
//     processArray();
//     return 0;
// }
