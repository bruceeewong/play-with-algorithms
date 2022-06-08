//
// Created by bruski on 6/15/20.
//

#ifndef SELECTIONSORT_SORTTESTHELPER_H
#define SELECTIONSORT_SORTTESTHELPER_H

#include <ctime>
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;

namespace SortTestHelper {
    // 生成n个元素的随机数组，每个元素的随机范围为[rangeL, rangeR]

    int *generateRandomArray(int n, int rangeL, int rangeR) {
        assert(rangeL < rangeR);
        int *arr = new int[n];
        srand(time(NULL));
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }
        return arr;
    }

    template<typename T>
    void printArray(T arr[], int n) {
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        return;
    }

    template<typename T>
    bool isSorted(T arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    void testSort(string sortName, void(*sort)(T[], int), T arr[], int n) {
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n));

        // 时钟周期差 除以每秒的时钟周期，得秒数
        cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
    }

    int *copyIntArray(int a[], int n) {
        int *arr = new int[n];
        // 头指针,尾指针, 目标指针
        copy(a, a + n, arr);
        return arr;
    }
}

#endif //SELECTIONSORT_SORTTESTHELPER_H