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

int main() {
    int n = 10000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 10);
    int *arr1 = SortTestHelper::copyIntArray(arr, n);

//    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
//    SortTestHelper::testSort("Merge Sort", mergeSort, arr, n);
//    SortTestHelper::testSort("mergeSortBU", mergeSortBU, arr1, n);

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

    delete[] arr;
    delete[] arr1;
    return 0;
}