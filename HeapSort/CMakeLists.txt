cmake_minimum_required(VERSION 3.16)
project(HeapSort)

set(CMAKE_CXX_STANDARD 14)

add_executable(HeapSort main.cpp MergeSort.h QuickSort.h SortTestHelper.h)