#include <iostream>
#include "SortTestHelper.h"
#include "SelectionSort.h"

// 原版插入排序
// InsertionSort: 0.28968 s
template<typename T>
void insertionSort1(T arr[], int n) {
    for (int i = 1; i < n; i ++) {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j --) {
            swap(arr[j], arr[j - 1]);
        }
    }
}

// 优化交换部分,改为赋值
// InsertionSort: 0.067853 s
template<typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i ++) {
        T e = arr[i];
        int j;  // 保存e 应该插入的下标位置
        for (j = i; j > 0 && arr[j-1] > e; j --) {
            arr[j] = arr[j - 1];  // 将交换换为赋值
        }
        // 最后执行插入
        arr[j] = e;
    }
}


int main() {
    int n = 10000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 10);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);

//    SortTestHelper::testSort("Insertion Sort1", insertionSort1, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
    SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);

    delete[] arr;
    delete[] arr1;
    return 0;
}