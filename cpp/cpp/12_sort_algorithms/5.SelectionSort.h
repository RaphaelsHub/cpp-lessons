#pragma once

void MinSort(int* arr)
{
    for (int i = 0; i < 10-1; i++)
    {
        int min_index=i;
        for (int x = min_index+1; x < 10; x++)
        {
            if(arr[x]<arr[min_index])
                min_index = x;
        }
        const int tmp = arr[i];
        arr[i]=arr[min_index];
        arr[min_index]=tmp;
    }
}