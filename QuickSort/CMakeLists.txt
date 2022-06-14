cmake_minimum_required(VERSION 3.16)
project(QuickSort)

set(CMAKE_CXX_STANDARD 14)

add_executable(QuickSort main.cpp ../HeapSort/main.cpp ../HeapSort/MaxHeap.h)