#include <iostream>
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"

template<typename T>
void shellSort(T arr[], int n) {
    // 希尔排序, 选取增量, 跳阶分组, 对每个分组执行插入排序；再缩小增量
    // 直到增量到1 时, 数组以及基本排好序, 最后在完整地执行一遍插入排序即可
    int h = 1;
    // 最大增量的选取, 是个数学题
    // N 为数组长度，K 为当前增量
    // 若增量序列取K = 2^x 时间复杂度是O(n^2)
    // 若增量序列取K = 3x + 1, 时间复杂度是O(n^2)
    while (h < n / 3) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        for (int i = 0; i < n; i++) {
            T e = arr[i];
            int j;
            // 将区间划为 [0, h-1] [h, 2h-1] ...
            for (j = i; j >= h && arr[j - 1] > e; j -= h) {
                arr[j] = arr[j - h];
            }
            arr[j] = e;
        }

        h /= 3;  // 增量缩小
    }
}


// 比较SelectionSort, InsertionSort和BubbleSort和ShellSort四种排序算法的性能效率
// ShellSort是这四种排序算法中性能最优的排序算法
int main() {
    int n = 20000;

    // 测试1 一般测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;

    int *arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);
    int *arr4 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
    SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    int swapTimes = 100;

    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;

    arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
    SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    return 0;
}
