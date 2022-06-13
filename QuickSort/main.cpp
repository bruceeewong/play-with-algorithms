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
    if (n <= 16) {
        return __insertionSort(arr, 0, n - 1);
    }
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
void quickSort2(T arr[], int n) {
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


template<typename T>
int __selectionPartition(T arr[], int l, int r) {
    int p = rand() % (r-l+1) + l;
    swap(arr[l], arr[p]);
    T pivot = arr[l];

    // arr[l+1...p] < pivot, arr[p+1, r] > p
    int j = l;
    for (int i = l + 1; i <= r; i ++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[j + 1]);
            j ++;
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

template<typename T>
T __selection(T arr[], int l, int r, int k) {
    if (l == r) return arr[l];

    int p = __selectionPartition(arr, l, r);

    if (k == p) return arr[p];
    if (k < p) return __selection(arr, l, p - 1, k);
    return __selection(arr, p + 1, r, k);
}

template<typename T>
T getKthNumByQuickSort(T arr[], int n, int k) {
    srand(time(NULL));
    return __selection(arr, 0, n - 1, k);
}


int getKthBySort(int arr[], int n, int k) {
    int *help = new int[n];
    for (int i = 0; i < n; i++) {
        help[i] = arr[i];
    }
    mergeSort(help, n);
    return help[k];
}


void testGetKthNum() {
    int N = 2;
    int *arr = new int[]{4, 2, 6, 1, 5, 7};
    int n = 6;
    assert(getKthBySort(arr, n, N) == 4);
    assert(getKthNumByQuickSort(arr, n, N) == 4);
}


int main() {
    int n = 100000;
//    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 10);
    // array that contains many duplicated elements
    int *arr = SortTestHelper::generateRandomArray(n, 0, 10);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Quick Sort", quickSort, arr, n);
    SortTestHelper::testSort("Quick Sort2", quickSort2, arr1, n);
    SortTestHelper::testSort("Quick Sort3", quickSort3, arr2, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr3, n);

    delete[] arr;
    delete[] arr1;
    delete[] arr2;

    testGetKthNum();
    return 0;
}