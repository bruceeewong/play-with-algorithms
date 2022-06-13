//
// Created by bruski on 6/18/20.
//

#ifndef INSERTIONSORT_SELECTIONSORT_H
#define INSERTIONSORT_SELECTIONSORT_H

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
    __mergeSort(arr, 0, n - 1);
}

#endif //INSERTIONSORT_SELECTIONSORT_H
