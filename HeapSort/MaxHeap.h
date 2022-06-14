//
// Created by Bruski on 2022/6/14.
//

#ifndef QUICKSORT_MAXHEAP_H
#define QUICKSORT_MAXHEAP_H

#include <cassert>
#include <cmath>

using namespace std;

template<typename Item>
class MaxHeap {
private:
    Item *data;
    int count;
    int capacity;

    void shiftUp(int index) {
        while (index > 1 && data[index / 2] < data[index]) {
            swap(data[index / 2], data[index]);
            index /= 2;
        }
    }

    void shiftDown(int index) {
        // if the element of index has child (i.e. at least has left child)
        while (index * 2 <= count) {
            int j = index * 2;
            if (j + 1 <= count && data[j + 1] > data[j]) {
                j ++;  // if right child exists and is larger than left child, update index
            }
            if (data[index] >= data[j]) break;  // element at index is fit

            swap(data[index], data[j]);
            index = j;
        }
    }

    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }

public:
    MaxHeap(int capacity) {
        data = new Item[capacity + 1];  // 索引从1开始，空出0不用
        count = 0;
        this->capacity = capacity;
    }

    MaxHeap(Item arr[], int n) {
        data = new Item[n + 1];
        capacity = n;
        count = n;
        for (int i = 0; i < n; i ++) {
            data[i + 1] = arr[i];
        }
        // 从后往前，第一个非叶子节点开始做shift down
        for (int i = count / 2; i >= 1; i --) {
            shiftDown(i);
        }
    }

    ~MaxHeap() {
        delete[] data;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    void insert(Item item) {
        assert(this->count < this->capacity);
        count ++;  // index starts from 1
        data[count] = item;
        shiftUp(count);
    }

    Item extractMax() {
        assert(count > 0);
        Item result = data[1];
        swap(data[1], data[count]);
        count --;
        shiftDown(1);
        return result;
    }

    // 以树状打印整个堆结构
    void testPrint(){

        // 我们的testPrint只能打印100个元素以内的堆的树状信息
        if( size() >= 100 ){
            cout<<"This print function can only work for less than 100 int";
            return;
        }

        // 我们的testPrint只能处理整数信息
        if( typeid(Item) != typeid(int) ){
            cout <<"This print function can only work for int item";
            return;
        }

        cout<<"The max heap size is: "<<size()<<endl;
        cout<<"Data in the max heap: ";
        for( int i = 1 ; i <= size() ; i ++ ){
            // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
            assert( data[i] >= 0 && data[i] < 100 );
            cout<<data[i]<<" ";
        }
        cout<<endl;
        cout<<endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            string line1 = string(max_level_number*3-1, ' ');

            int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            cout<<line1<<endl;

            if( level == max_level - 1 )
                break;

            string line2 = string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            cout<<line2<<endl;

            cur_tree_max_level_number /= 2;
        }
    }
};

#endif //QUICKSORT_MAXHEAP_H
