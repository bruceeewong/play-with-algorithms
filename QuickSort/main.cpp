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

// return index j, arrange array to make arr[l, j-1] < v, arr[j+1, r] > v
// 双路快排
template<typename T>
int __partition2(T arr[], int l, int r) {
    swap(arr[l], arr[rand() % (r - l + 1) + l]); // 随机选枢纽元，并挪到最左侧
    T pivot = arr[l];

    int i = l + 1, j = r;
    // i++, on the left side of i are all <= pivot
    // j--, on the right side of j are all >= pivot
    while (true) {
        while (i <= r && arr[i] < pivot) i ++;
        while (j >= l + 1 && arr[j] > pivot) j --;
        if (i > j) break;

        swap(arr[i], arr[j]);
        i ++;
        j --;
    }
    // j is now at the right end of elements that <= pivot
    swap(arr[l], arr[j]);
    return j;
}

template<typename T>
void __quickSort2(T arr[], int l, int r) {
    if (l >= r) return;

    int p = __partition2(arr, l, r);
    __quickSort2(arr, l, p - 1);
    __quickSort2(arr, p + 1, r);
}

// 优化交换部分,改为赋值
// InsertionSort: 0.067853 s
template<typename T>
void quickSort2(T arr[], int n) {
    srand(time(NULL));
    __quickSort2(arr, 0, n - 1);
}





int main() {
    int n = 100000;
//    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 10);
    // array that contains many duplicated elements
    int *arr = SortTestHelper::generateRandomArray(n, 0, 10);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Quick Sort", quickSort, arr, n);
    SortTestHelper::testSort("Quick Sort2", quickSort2, arr1, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    return 0;
}