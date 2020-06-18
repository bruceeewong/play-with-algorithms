//
// Created by bruski on 6/18/20.
//

#ifndef BUBBLESORT_INSERTIONSORT_H
#define BUBBLESORT_INSERTIONSORT_H

// 优化交换部分,改为赋值
// InsertionSort: 0.067853 s
template<typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i ++) {
        T e = arr[i];
        int j;  // 保存e 应该插入的下标位置
        for (j = i; j > 0 && arr[j-1] > e; j --) {
            arr[j] = arr[j - 1];  // 将交换换为赋值
        }
        // 最后执行插入
        arr[j] = e;
    }
}


#endif //BUBBLESORT_INSERTIONSORT_H
