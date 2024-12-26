#pragma once

#include <iostream>
#include <cassert>

void allocate(int m, int n, int ***mass)
{
    int **p = new int *[m];
    for (int x = 0; x < m; x++)
        p[x] = new int[n];
    *mass = p;
}

void fill(int m, int n, int **mass)
{
    for (int x = 0; x < m; x++)
        for (int y = 0; y < n; y++)
            std::cin >> mass[x][y];
}

void print(int m, int n, int **mass)
{
    for (int x = 0; x < m; x++)
        for (int y = 0; y < n; y++)
            std::cout << mass[x][y] << " ";
}

void find_min(int f, int h, int **mass, int S, int str)
{
    int min = mass[f][h];
    for (int q = f - 1; q <= f + 1; q++)
        for (int e = h - 1; e <= h + 1; e++)
        {
            if (q < 0 || q >= S || e < 0 || e >= str || (q == f && e == h))
                continue;
            else if (mass[q][e] < min)
                min = mass[q][e];
        }
    std::cout << min << " ";
}

// Это не функция main(), но я оставлю ее для тестирования кода.
// В вашем коде должна быть функция main(), чтобы программа запускалась.
// int main() {
//     int COLS, ROWS;
//     std::cin >> ROWS >> COLS;
//     int **matrix = nullptr;
//     allocate(ROWS, COLS, &matrix);
//     fill(ROWS, COLS, matrix);
//     print(ROWS, COLS, matrix);
//     for (int g = 0; g < COLS; g++)
//         for (int v = 0; v < ROWS; v++)
//             find_min(g, v, matrix, COLS, ROWS);
//     return 0;
// }
