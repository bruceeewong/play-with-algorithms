using namespace std;

#include <iostream>
#include "SortTestHelper.h"
#include "Student.h"

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

int main() {
    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    selectionSort(a, 10);
    for (int i = 0; i < 10; i++) {
        cout << a[i] << " ";
    }

    cout << endl;

    float b[4] = {4.4, 3.3, 2.2, 1.1};
    selectionSort(b, 4);
    for (int i = 0; i < 4; i++) {
        cout << b[i] << " ";
    }

    cout << endl;

    string c[4] = {"D", "C", "B", "A"};
    selectionSort(c, 4);
    for (int i = 0; i < 4; i++) {
        cout << c[i] << " ";
    }
    cout << endl;

    Student d[4] = {{"D", 90},
                    {"C", 100},
                    {"B", 90},
                    {"A", 70}};
    selectionSort(d, 4);
    for (int i = 0; i < 4; i++) {
        cout << d[i] << " ";
    }

    int n = 10000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//    SortTestHelper::printArray(arr, n);
    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    delete[] arr;
    return 0;
}
