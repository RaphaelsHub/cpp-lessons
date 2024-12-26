#pragma once
#include <cstring> // Include <cstring> for memset

inline void CountingSort(int *num, int length)
{
    // Find the maximum value in the array
    int max = num[0];
    for (int i = 1; i < length; i++)
    {
        if (num[i] > max)
            max = num[i];
    }

    // Initialize the array to count values
    int *sortedArr = new int[max + 1]; // Allocate memory dynamically
    std::memset(sortedArr, 0, sizeof(int) * (max + 1)); // Fill the array with zeros

    // Count the occurrences of each element in the array
    for (int i = 0; i < length; i++)
    {
        sortedArr[num[i]]++;
    }

    // Restore the sorted array from the counted values
    int i = 0, j = 0;
    while (i <= max)
    {
        if (sortedArr[i] != 0)
        {
            num[j++] = i;
            sortedArr[i]--;
        }
        else
        {
            i++;
        }
    }

    delete[] sortedArr; // Deallocate memory to avoid memory leaks
}
