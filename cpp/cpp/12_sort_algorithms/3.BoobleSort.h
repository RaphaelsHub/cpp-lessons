#pragma once

inline void BubleSort(int *num, const int lenght)
{
    for (int i = 0; i<lenght; i++)
    {
        for (int y = i+1;y<lenght;y++)
        {
            if(num[i]>num[y])
            {
                const int tmp = num[i];
                num[i]=num[y];
                num[y]=tmp;
            }
        }
    }
}
