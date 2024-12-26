#pragma once

#include <iostream>
#include <cstring>

void processString()
{
    char source[51]; // 50 символов + завершающий нуль
    std::cin >> source;

    int length = strlen(source);
    int count = 1;
    char tmp = 0;

    for (int x = 0; x < length; x++)
        for (int y = x + 1; y < length; y++)
            if (source[x] > source[y])
            {
                tmp = source[x];
                source[x] = source[y];
                source[y] = tmp;
            }

    for (int z = 0; source[z]; z++)
    {
        if (source[z] == source[z + 1])
            count++;
        else
        {
            std::cout << source[z] << " " << count << " ";
            count = 1;
        }
    }
}

// Это не функция main(), но я оставлю ее для тестирования кода.
// В вашем коде должна быть функция main(), чтобы программа запускалась.
// int main() {
//     processString();
//     return 0;
// }
