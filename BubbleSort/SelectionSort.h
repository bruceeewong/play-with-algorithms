//
// Created by bruski on 6/18/20.
//

#ifndef BUBBLESORT_SELECTIONSORT_H
#define BUBBLESORT_SELECTIONSORT_H

template<typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

#endif //BUBBLESORT_SELECTIONSORT_H
