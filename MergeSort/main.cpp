#include "SortTestHelper.h"
#include "InsertionSort.h"

template<typename T>
void __insertionSort(T arr[], int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        T val = arr[i];
        int j;
        for (j = i; j > l && val < arr[j - 1]; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = val;
    }
}

// merge arr[l...r]
template<typename T>
void __merge(T arr[], int l, int mid, int r) {
    T help[r - l + 1];
    // init helper arr by range
    for (int i = l; i <= r; i++) {
        help[i - l] = arr[i];
    }
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = help[j - l];
            j++;
        } else if (j > r) {
            arr[k] = help[i - l];
            i++;
        } else if (help[i - l] < help[j - l]) {
            arr[k] = help[i - l];
            i++;
        } else {
            arr[k] = help[j - l];
            j++;
        }
    }
}


// mergeSort arr[l ... r]
template<typename T>
void __mergeSort(T arr[], int l, int r) {
    if (r - l <= 15) {
        __insertionSort(arr, l, r);
        return;
    }
    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);

    if (arr[mid] <= arr[mid + 1]) return;
    __merge(arr, l, mid, r);
}

template<typename T>
void mergeSort(T arr[], int n) {
    assert(n > 0);
    __mergeSort(arr, 0, n - 1);
}

template<typename T>
void mergeSortBU(T arr[], int n) {
    if (n <= 16) {
        __insertionSort(arr, 0, n - 1);
        return;
    }
    for (int sz = 1; sz <= n; sz = 2 * sz) {
        // 下一次跳2个sz接着归并
        // i + sz < n 保证了后段区间的存在
        for (int i = 0; i + sz < n; i += 2 * sz) {
            int l = i;
            int mid = i + sz - 1;
            int r = min(i + 2 * sz - 1, n - 1);

            if (arr[mid] < arr[mid + 1]) continue;  // 两段已经有序，直接下一步
            // 对 arr[i...i+sz-1] 和 arr[i+sz...i+2*sz-1] 进行归并
            __merge(arr, l, mid, r);  // 后段可能不足 sz 个元素，只取到末尾
        }
    }
}


int main() {
    int n = 10000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 10);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);

//    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr, n);
    SortTestHelper::testSort("mergeSortBU", mergeSortBU, arr1, n);

    delete[] arr;
    delete[] arr1;
    return 0;
}