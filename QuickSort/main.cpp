#include <iostream>
#include "SortTestHelper.h"
#include "MergeSort.h"

// return index j, arrange array to make arr[l, j-1] < v, arr[j+1, r] > v
template<typename T>
int __partition(T arr[], int l, int r) {
    swap(arr[l], arr[rand() % (r - l + 1) + l]); // 随机选枢纽元，并挪到最左侧
    T pivot = arr[l];

    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < pivot) {
            swap(arr[j + 1], arr[i]);
            j++;
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

template<typename T>
void __quickSort(T arr[], int l, int r) {
    if (l >= r) return;

    int p = __partition(arr, l, r);
    __quickSort(arr, l, p - 1);
    __quickSort(arr, p + 1, r);
}

// 优化交换部分,改为赋值
// InsertionSort: 0.067853 s
template<typename T>
void quickSort(T arr[], int n) {
    srand(time(NULL));
    __quickSort(arr, 0, n - 1);
}


int main() {
    int n = 10000;
//    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 10);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Quick Sort", quickSort, arr, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);

    delete[] arr;
    delete[] arr1;
    return 0;
}