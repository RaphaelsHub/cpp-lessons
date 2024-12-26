#pragma once
#include <cstring> // Include <cstring> for memset

inline void Merge(int* num, int begin, int mid, int end)
{
    int *sortedArr = new int[end - begin + 1];
    std::memset(sortedArr, 0, sizeof(int) * (end - begin + 1));

    int i = 0;
    while (begin <= mid && mid <= end)
    {
        sortedArr[i++] = num[begin] <= num[mid] ? num[begin++] : num[mid++];
    }

    while (begin <= mid)
    {
        sortedArr[i++] = num[begin++];
    }

    while (mid <= end)
    {
        sortedArr[i++] = num[mid++];
    }

    for (int j = 0; j < i; j++)
        num[begin + j] = sortedArr[j];

    delete[] sortedArr; // Deallocate memory to avoid memory leaks
}

inline void MergeSort(int* num, int begin, int end)
{
    if (begin < end)
    {
        const int mid = (begin + end) / 2;
        MergeSort(num, begin, mid);
        MergeSort(num, mid + 1, end);
        Merge(num, begin, mid, end);
    }
}
