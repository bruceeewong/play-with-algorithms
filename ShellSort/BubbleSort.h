//
// Created by bruski on 6/18/20.
//

#ifndef SHELLSORT_BUBBLESORT_H
#define SHELLSORT_BUBBLESORT_H

template<typename T>
void bubbleSort(T arr[], int n) {
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

#endif //SHELLSORT_BUBBLESORT_H
