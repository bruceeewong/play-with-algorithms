//
// Created by Bruski on 2022/6/14.
//

#include <iostream>
#include "MaxHeap.h"


int main () {
    using namespace std;

    MaxHeap<int> maxHeap = MaxHeap<int>(100);
    cout << maxHeap.size() << endl;

    srand(time(NULL));
    for (int i = 0; i < 15; i ++) {
        maxHeap.insert(rand() % 100);
    }
    maxHeap.testPrint();
    return 0;
}