#pragma once

#include "1.MergeSort.h"
#include "3.BoobleSort.h"
#include "4.InsertionSort.h"
#include "5.SelectionSort.h"
#include "6.CountingSort.h"

void CallAllSortingAlgorithms()
{
    int nums[10] = {2,6,8,2,3,5,7,8,5,2};
    BubleSort(nums,10);
    int nums1[10] = {2,6,8,2,3,5,7,8,5,2};
    InsertionSort(nums1, 10);
    int nums2[10] = {2,6,8,2,3,5,7,8,5,2};
    MinSort(nums2);
    int nums3[10] = {2,6,8,2,3,5,7,8,5,2};
    CountingSort(nums3,10);
    int nums4[10] = {2,6,8,2,3,5,7,8,5,2};
    //MergeSort(nums4,0,9);
}