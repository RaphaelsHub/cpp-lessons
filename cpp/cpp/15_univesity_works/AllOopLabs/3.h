#pragma once

#include <iostream>

void processMatrix()
{
    int rows = 0, cols = 0;
    std::cin >> rows >> cols;

    const int NUM_ROWS = rows;
    const int NUM_COLS = cols;

    int matrix[NUM_ROWS][NUM_COLS];
    int count = 0, mainCounter = 0, mainNum = 0, sum = 0;

    for (int i = 0; i < NUM_ROWS; i++)
        for (int j = 0; j < NUM_COLS; j++)
            std::cin >> matrix[i][j];

    for (int x = 0; x < NUM_ROWS; x++)
        for (int y = 0; y < NUM_COLS - 1; y++)
        {
            if (matrix[x][y] == matrix[x][y + 1])
            {
                count++;
                mainNum = matrix[x][y + 1];
            }
            else if (count > mainCounter)
            {
                mainCounter = count;
                count = 0;
            }
            else
                count = 0;
        }

    for (int z = 0; z < NUM_ROWS; z++)
        for (int g = 0; (g <= z) && (g <= NUM_ROWS - z - 1); g++)
            sum += matrix[z][g];

    std::cout << mainNum << " " << sum << std::endl;
}

// Это не функция main(), но я оставлю ее для тестирования кода.
// В вашем коде должна быть функция main(), чтобы программа запускалась.
// int main() {
//     processMatrix();
//     return 0;
// }
