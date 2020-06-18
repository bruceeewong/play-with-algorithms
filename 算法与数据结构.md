# 算法与数据结构 - 综合提升 C++ 版

> 笔记时间 2020/06/15

## 排序算法

### 选择排序 Selection Sort

思路：遍历数组，将当前下标记下，寻找当前下标后面后续更小的值，如果有，更新最小值的下标; 遍历结束，交换当前元素与最小值元素的位置。

时间复杂度 O(n^2)

```cpp
template<typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}
```

### 插入排序 Insertion Sort

#### 基础实现

从下标为 `1` 开始往后遍历, 与下标之前的元素比较. 若小于前一个,交换位置, 直到下标为` 1`.

```cpp
template<typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j-1] > arr[j]; j--) {
            swap(arr[j-1], arr[j]);
        }
    }
}
```

#### 优化

减少交换的操作, 暂存要插入的数据,做比较,找到最后的位置,再执行插入, 性能提升很多

```cpp
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
```

#### 插入排序 VS 选择排序

两者效率在随机乱序的数组排序中, 插入排序稍胜一筹

但在近乎有序的数组中, 插入排序可以达到 `O(n)` 的复杂度, 所以常用来做复杂算法的子过程.

### 冒泡排序 Bubble Sort

#### 基本思路

定义一个是否执行了交换的标识,  遍历`[1,n)`数组下标, 如果 前一个比到当前的大, 交换这两个的位置, 每次循环后, 最大的元素会浮到末尾；此时判断本轮是否发生了交换, 如果是, 还需进行下一次的循环, 此时 n --(优化: 下一轮不再考虑本轮最大的元素了) . 否则当循环结束了标识仍为 false, 说明此时已经排好序, 排序结束.

```cpp
template<typename T>
void bubbleSort(T arr[], int n) {
    bool isSwapped;
    
    do {
        isSwapped = false;
        for (int i = 1; i < n; i ++) {
            if (arr[i-1] > arr[i]) {
                swap(arr[i-1], arr[i]);
                isSwapped = true;
            }
        }
        n --;  // 每一次都将最大元素放到最后, 下一次循环不再考虑
    } while (isSwapped);
}
```

#### 优化

将bool换成下标, 每次交换更新下标；

如果新下标==0, 循环结束

否则, 将最后一次交换的下标作为下一轮的n

```cpp
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
```



### 希尔排序 Shell Sort

#### 基本思路

基于数组长度选取最大步长, 这里直接用研究结论:

```
// N 为数组长度，K 为当前增量
// 若增量序列取K = 2^x 时间复杂度是O(n^2)
// 若增量序列取K = 3x + 1, 时间复杂度是O(n^2)
```

这里选择 第二种, 遍历数组`[1,n)`的元素, 对以步长分好的组进行插入排序, 结束后将步长 / 3.

判断步长是否 大于等于 1, 如果是继续希尔排序, 否则, 排序结束

```cpp
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
```

#### 结果比较

##### 测试1 乱序数组排序(n = 20000)

- 希尔排序: 0.019095 s

- 插入排序:0.25919 s
- 选择排序:0.42556 s
- 冒泡排序:1.90432 s

##### 测试2 近乎有序数组排序(n = 20000)

- 希尔排序: 0.00742 s

- 插入排序:0.003506 s
- 选择排序:0.416048 s
- 冒泡排序:0.472879 s

