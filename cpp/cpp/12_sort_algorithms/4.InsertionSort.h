#pragma once

inline void InsertionSort(int num[10], const int lenght)
{
    for (int i = 1; i < lenght; i++)
    {
        const int key = num[i];
        int j;
        for (j = i - 1; j >= 0 && num[j] > key; j--)
        {
            num[j + 1] = num[j];
            num[j]=key;
        }
        //num[j+1]=key;
    }
}
