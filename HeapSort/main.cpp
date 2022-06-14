//
// Created by Bruski on 2022/6/14.
//

#include <iostream>
#include "MaxHeap.h"
#include "SortTestHelper.h"
#include "MergeSort.h"
#include "QuickSort.h"

void heapSort1(int arr[], int n) {
    MaxHeap<int> maxHeap = MaxHeap<int>(n);
    for (int i = 0; i < n; i++) {
        maxHeap.insert(arr[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = maxHeap.extractMax();
    }
}

void heapSort2(int arr[], int n) {
    MaxHeap<int> maxHeap = MaxHeap<int>(arr, n);
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = maxHeap.extractMax();
    }
}

void __shiftDown(int arr[], int n, int index) {
    // 重复至叶子结点停止(下标从0开始，则需<n)
    while (2 * index + 1 < n) {
        // 检查左右孩子，找到最大孩子的下标
        int maxChildIndex = 2 * index + 1;
        if (maxChildIndex + 1 < n && arr[maxChildIndex + 1] > arr[maxChildIndex]) {
            maxChildIndex++;
        }
        // 如果当前节点不比最大孩子小，则停止
        if (arr[index] >= arr[maxChildIndex]) break;

        // 与最大孩子交换值，更新下标为孩子下标
        swap(arr[index], arr[maxChildIndex]);
        index = maxChildIndex;
    }
}

void heapSort3(int arr[], int n) {
    int lastEleIndex = n - 1;
    // Heapify 建立最大堆
    for (int i = (lastEleIndex - 1) / 2; i >= 0; i--) {
        __shiftDown(arr, n, i);
    }
    // 原地堆排序，排至子最大堆只剩一个元素即可
    for (int i = lastEleIndex; i > 0; i--) {
        swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0); // n逐步减小，heapify子堆
    }
}

void testMaxHeap() {
    MaxHeap<int> maxHeap = MaxHeap<int>(100);
    cout << maxHeap.size() << endl;

    srand(time(NULL));
    for (int i = 0; i < 15; i++) {
        maxHeap.insert(rand() % 100);
    }
    maxHeap.testPrint();

    while (!maxHeap.isEmpty()) {
        cout << maxHeap.extractMax() << " ";
    }
    cout << endl;
}

void testHeapSort() {
    int n = 1000000;
    int rangeL = 0, rangeR = n;
    int *arr = SortTestHelper::generateRandomArray(n, rangeL, rangeR);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
    int *arr4 = SortTestHelper::copyIntArray(arr, n);
    int *arr5 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test for random array, n: " << n << " , range: [" << rangeL << ", " << rangeR << "]" << endl;
    SortTestHelper::testSort("Merge Sort", mergeSort, arr, n);
    SortTestHelper::testSort("QuickSort", quickSort, arr1, n);
    SortTestHelper::testSort("QuickSort 3Ways", quickSort3, arr2, n);
    SortTestHelper::testSort("HeapSort 1", heapSort1, arr3, n);
    SortTestHelper::testSort("HeapSort 2", heapSort2, arr4, n);
    SortTestHelper::testSort("HeapSort 3", heapSort3, arr5, n);
    cout << endl;

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    int swapTimes = 10;
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test for nearly ordered array, n: " << n << " , swap times: " << swapTimes << "" << endl;
    SortTestHelper::testSort("Merge Sort", mergeSort, arr, n);
    SortTestHelper::testSort("QuickSort", quickSort, arr1, n);
    SortTestHelper::testSort("QuickSort 3Ways", quickSort3, arr2, n);
    SortTestHelper::testSort("HeapSort 1", heapSort1, arr3, n);
    SortTestHelper::testSort("HeapSort 2", heapSort2, arr4, n);
    SortTestHelper::testSort("HeapSort 3", heapSort3, arr5, n);
    cout << endl;

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    n = 1000000;
    rangeL = 0, rangeR = 10;
    arr = SortTestHelper::generateRandomArray(n, rangeL, rangeR);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test for random array, n: " << n << " , range: [" << rangeL << ", " << rangeR << "]" << endl;
    SortTestHelper::testSort("Merge Sort", mergeSort, arr, n);
    SortTestHelper::testSort("QuickSort", quickSort, arr1, n);
    SortTestHelper::testSort("QuickSort 3Ways", quickSort3, arr2, n);
    SortTestHelper::testSort("HeapSort 1", heapSort1, arr3, n);
    SortTestHelper::testSort("HeapSort 2", heapSort2, arr4, n);
    SortTestHelper::testSort("HeapSort 3", heapSort3, arr5, n);
    cout << endl;

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
}


int main() {
    using namespace std;
//    testMaxHeap();
    testHeapSort();
    return 0;
}