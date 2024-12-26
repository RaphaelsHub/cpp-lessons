#pragma once

#include <iostream>

using namespace std;

// Function prototypes for different array parameter passing methods
void PrintArrayPointer(int* arr);
void PrintArrayBrackets(int arr[]);
void PrintArrayFixedSize(int arr[3]);
void PrintArrayPointerToArray(int (*arr)[2]);

// Lesson 1: Sum of diagonals and quarters of a matrix
void CalculateDiagonalSums()
{
    constexpr int n = 3;
    int a[n][n];
    int sum = 0;
    int totalSum = 0;

    // Initializing the matrix
    for (int i = 0; i < n; i++)
        for (int y = 0; y < n; y++)
            a[i][y] = i * y;
    
    // Sum of main and secondary diagonals
    for (int i = 0; i < n; i++)
    {
        sum += a[i][i];
        totalSum += a[i][n - i - 1];
    }

    // Sum of elements above the main diagonal
    sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            sum += a[i][j];

    // Sum of elements above the secondary diagonal
    sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i; j++)
            sum += a[i][j];

    // Sum of 1st quarter
    sum = 0;
    for (int i = 0; i < n / 2; i++)
        for (int j = i; j < n - i; j++)
            sum += a[i][j];

    // Sum of 2nd quarter
    sum = 0;
    for (int i = n - 1, z = 0; i >= n / 2; i--, z++)
        for (int j = 0 + z; j < n - z; j++)
            sum += a[j][i];

    // Sum of 3rd quarter
    sum = 0;
    for (int i = n - 1, z = 0; i >= n / 2; i--, z++)
        for (int j = 0 + z; j < n - z; j++)
            sum += a[i][j];
          
    // Sum of 4th quarter
    sum = 0;
    for (int i = 0, z = 0; i < n / 2; i++, z++)
        for (int j = 0 + z; j < n - z; j++)
            sum += a[j][i];
}

// Lesson 2: Push array elements to the right
void ShiftRight(int arr[3])
{
    const int c = arr[2];
    for (int i = 3 - 1; i > 0; i--)
        arr[i] = arr[i - 1];
    arr[0] = c;
}

// Lesson 3: Merge and sort two arrays
void MergeSortArrays(int arr[], int array[])
{
    int i = 0, j = 0;
    int c[6];
    
    while (i < 3 && j < 3)
    {
        arr[i] >= array[j] ? c[i + j] = array[j] : c[i + j] = arr[i];
        arr[i] >= array[j] ? ++j : ++i;
    }
    while (i < 3)
    {
        c[i + j] = arr[i];
        ++i;
    }
    while (j < 3)
    {
        c[i + j] = array[j];
        ++j;
    }
}

int CallAllFunctionsArray()
{
    int array[] = { 1, 2, 3 };
    int array1[2][2] = {{1, 2}, {3, 4}};

    // Uncomment to test different array parameter passing methods
    // PrintArrayPointer(array);
    // PrintArrayBrackets(array);
    // PrintArrayFixedSize(array);
    // PrintArrayPointerToArray(array1);

    // Some array tasks
    CalculateDiagonalSums();
    ShiftRight(array);
    MergeSortArrays(array, array);
    return 0;
}
