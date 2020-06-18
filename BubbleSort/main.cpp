#include <iostream>
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "InsertionSort.h"

template<typename T>
void bubbleSort(T arr[], int n) {
    bool isSwapped;

    do {
        isSwapped = false;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                isSwapped = true;
            }
        }
        n--;  // 每一次都将最大元素放到最后, 下一次循环不再考虑
    } while (isSwapped);
}

template<typename T>
void bubbleSort2(T arr[], int n) {
    int newn;

    do {
        newn = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                newn = i;  // 记录最后一次交换的位置, 下一轮直接以此位置为n
            }
        }
        n = newn;
    } while (newn > 0);
}

int main() {
    int n = 20000;

    // 测试1 一般测试
    cout<<"Test for random array, size = "<<n<<", randome range [0, "<<n<<"]"<<endl;

    int *arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);
    int *arr4 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
    SortTestHelper::testSort("Bubble Sort 2", bubbleSort2, arr4, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    // 测试2 测试近乎有序的数组
    int swapTimes = 100;

    cout<<"Test for nNearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;

    arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
    SortTestHelper::testSort("Bubble Sort 2", bubbleSort2, arr4, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    cout<<endl;

    // 测试3 测试完全有序的数组
    // 对于完全有序的数组，冒泡排序法也将成为O(n)级别的算法
    swapTimes = 0;
    n = 10000000;    // 由于插入排序法和冒泡排序法在完全有序的情况下都将成为O(n)算法
    // 所以我们的测试数据规模变大，为1000,0000
    cout<<"Test for ordered array, size = " << n << endl;

    arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);

    // 在这种情况下，不再测试选择排序算法
    //SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
    SortTestHelper::testSort("Bubble Sort 2", bubbleSort2, arr4, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    return 0;
}
