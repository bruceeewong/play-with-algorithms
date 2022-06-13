#include "SortTestHelper.h"
#include "InsertionSort.h"
#include <cmath>

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

template<typename T>
class Node {
public:
    T val;
    Node<T> *next;

public:
    Node(T _val) {
        val = _val;
        next = nullptr;
    }

    Node() {
        next = nullptr;
    }
};

template<typename T>
int _len(Node<T> *head) {
    int len = 0;
    Node<T> *cur = head;
    while (cur != nullptr) {
        len++;
        cur = cur->next;
    }
    return len;
}

template<typename T>
Node<T> *__mergeTwoLinkList(Node<T> *left, Node<T> *right) {
    Node<T> *dummyHead = new Node<T>();
    Node<T> *cur = dummyHead;
    while (left != nullptr && right != nullptr) {
        if (left->val < right->val) {
            cur->next = left;
            left = left->next;
        } else {
            cur->next = right;
            right = right->next;
        }
        cur = cur->next;
    }
    cur->next = left == nullptr ? right : left;
    return dummyHead->next;
}

template<typename T>
Node<T> *mergeSortForLinkList(Node<T> *head) {
    int len = _len(head);
    if (len < 2) return head;

    Node<T> *dummyHead = new Node<T>();
    dummyHead->next = head;

    for (int sz = 1; sz <= len; sz += sz) {
        int numOfSection = ceil(float(len) / float(2 * sz));
        Node<T> *prev = dummyHead;  // 用于衔接归并后的子链表的前一个节点
        Node<T> *sectionHead = dummyHead->next;  // 每轮子序列归并的开头

        for (int i = 0; i < numOfSection; i++) {
            // 处理待处理的小区块，分割左右，然后归并排序
            // 确定左区间开头
            Node<T> *left = sectionHead;
            // 尝试寻找本组的左区间的结尾（走sz - 1步)
            Node<T> *cur = left;

            for (int j = 0; j < sz - 1 && cur != nullptr; j++) {
                cur = cur->next;
            }
            if (cur == nullptr || cur->next == nullptr) {
                // 只有左边一截，本轮无需归并
                prev->next = left;
                break;
            }

            // 确定右区间的开头
            Node<T> *right = cur->next;
            cur->next = nullptr;  // 断掉左区间结尾与右区间的开头的链接
            cur = right;  // 游标定位至右区间的开头
            // 找到右区间的末尾
            for (int j = 0; j < sz - 1 && cur != nullptr; j++) {
                cur = cur->next;
            }
            if (cur == nullptr || cur->next == nullptr) {
                prev->next = __mergeTwoLinkList(left, right);
                break;
            }
            // 更新下一轮的头节点
            sectionHead = cur->next;
            // 切断右区间结尾与下一左区间的开头的链接
            cur->next = nullptr;
            // 执行归并
            prev->next = __mergeTwoLinkList(left, right);
            // 移动至末尾，用于衔接下一条链表
            while (prev->next != nullptr) {
                prev = prev->next;
            }
        }
    }

    return dummyHead->next;
}

template<typename T>
void print(Node<T> *head) {
    cout << "head > ";
    while (head != nullptr) {
        cout << head->val << " > ";
        head = head->next;
    }
    cout << "tail" << endl;
}

void testMergeSort() {
    int n = 10000;
    int rangeL = 0, rangeR = n;
    int *arr = SortTestHelper::generateRandomArray(n, rangeL, rangeR);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test for random array, n: " << n << " , range: [" << rangeL << ", " << rangeR << "]" << endl;
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("mergeSortBU", mergeSortBU, arr2, n);
    cout << endl;

    delete[] arr;
    delete[] arr1;
    delete[] arr2;

    int swapTimes = 10;
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr1 = SortTestHelper::copyIntArray(arr, n);
    arr2 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test for nearly ordered array, n: " << n << " , swap times: " << swapTimes << "" << endl;
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("mergeSortBU", mergeSortBU, arr2, n);
    cout << endl;

    delete[] arr;
    delete[] arr1;
    delete[] arr2;
}

void testMergeSortForLinkedList() {
    cout << "Test for linked list" << endl;
    Node<int> *head = new Node<int>(3);
    Node<int> *node1 = new Node<int>(2);
    Node<int> *node2 = new Node<int>(1);
    Node<int> *node3 = new Node<int>(2);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;

    print(head);
    head = mergeSortForLinkList(head);
    print(head);
}


int __countAndMerge(int arr[], int l, int mid, int r) {
    int *help = new int[r - l + 1];
    for (int i = l; i <= r; i++) {
        help[i - l] = arr[i];
    }

    int counter = 0;
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            //  左半部分已经处理完
            arr[k] = help[j - l];
            j++;
        } else if (j > r) {
            // 右半部分已经处理完
            arr[k] = help[i - l];
            i++;
        } else if (help[i - l] <= help[j - l]) {
            // 左半部分所指元素 <= 右半部分所指元素
            arr[k] = help[i - l];
            i++;
        } else {
            // 右侧的值比左侧的小，则右侧此值可与左侧未处理的值都构成逆序对，直接加上左侧未处理值的个数
            arr[k] = help[j - l];
            j++;

            counter += mid - i + 1;
        }
    }
    delete[] help;
    return counter;
}

int __inversionCount(int arr[], int l, int r) {
    if (l >= r) return 0;

    int mid = (l + r) / 2;
    int res1 = __inversionCount(arr, l, mid);
    int res2 = __inversionCount(arr, mid + 1, r);
    return res1 + res2 + __countAndMerge(arr, l, mid, r);
}

int countInverseNumberPairs(int arr[], int n) {
    return __inversionCount(arr, 0, n - 1);
}


int brutalCount(int arr[], int n) {
    int counter = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) counter += 1;
        }
    }
    return counter;
}

void testInverseNumberPairs() {
    int *arr = new int[]{8, 6, 2, 3, 1, 5, 7, 4};
    int *arr1 = SortTestHelper::copyIntArray(arr, 8);
    cout << "brutalCount: The number of Inverse Pairs is " << brutalCount(arr, 8) << endl;
    cout << "countByMergeSort: The number of Inverse Pairs is " << countInverseNumberPairs(arr1, 8);
    delete[] arr;
    delete[] arr1;

    // performance benchmark
    int n = 10000;
    int rangeL = 0, rangeR = n;
    arr = SortTestHelper::generateRandomArray(n, rangeL, rangeR);
    arr1 = SortTestHelper::copyIntArray(arr, n);

    cout << "Test for random array, n: " << n << " , range: [" << rangeL << ", " << rangeR << "]" << endl;
    SortTestHelper::testCountPerformance("count By MergeSort", countInverseNumberPairs , arr1, n);
    SortTestHelper::testCountPerformance("brutalCount", brutalCount, arr, n);
    cout << endl;
}

int main() {
//    testMergeSort();
//    testMergeSortForLinkedList();
    testInverseNumberPairs();
    return 0;
}