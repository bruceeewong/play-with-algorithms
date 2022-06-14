//
// Created by bruski on 6/18/20.
//

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
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
        while (i <= r && arr[i] < pivot) i++;
        while (j >= l + 1 && arr[j] > pivot) j--;
        if (i > j) break;

        swap(arr[i], arr[j]);
        i++;
        j--;
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
void quickSort(T arr[], int n) {
    if (n <= 16) {
        return __insertionSort(arr, 0, n - 1);
    }
    srand(time(NULL));
    __quickSort2(arr, 0, n - 1);
}


// 三路快排
template<typename T>
void __quickSort3(T arr[], int l, int r) {
    if (l >= r) return;

    // partition
    swap(arr[l], arr[rand() % (r - l + 1) + l]); // 随机选枢纽元，并挪到最左侧
    T pivot = arr[l];

    int lt = l; // arr[l+1, lt] < v
    int i = l + 1; // arr[lt, i) == v
    int gt = r + 1; // arr[gt, r] > v

    while (i < gt) {
        if (arr[i] < pivot) {
            swap(arr[lt + 1], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt - 1]);
            gt--;
        } else {
            i++;
        }
    }
    swap(arr[l], arr[lt]);
    lt--;// after swap, lt is one after the <v index;

    // recursion
    __quickSort3(arr, l, lt);
    __quickSort3(arr, gt, r);
}

template<typename T>
void quickSort3(T arr[], int n) {
    if (n <= 16) {
        return __insertionSort(arr, 0, n - 1);
    }
    srand(time(NULL));
    __quickSort3(arr, 0, n - 1);
}

#endif //QUICKSORT_H
