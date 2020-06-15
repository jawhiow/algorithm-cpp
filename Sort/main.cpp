//
// Created by JT on 2020/6/7.
//

#include <iostream>
#include "SortHelper.h"

using namespace std;

/*
 * 升序排序法
 * 选择排序升序算法: 每次选择最小的放到前面去
 * */
template<typename T>
void selectionSort(T arr[], int n) {
    if (arr == nullptr || n <= 0) return;
    for (int i = 0; i < n; ++i) {
        int min_num_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[min_num_idx] > arr[j]) {
                min_num_idx = j;
            }
        }
        if (min_num_idx == i) continue;
        swap(arr[i], arr[min_num_idx]);
    }
}

/*
 * 升序排序法
 * 插入排序法：相邻元素比较，寻找当前i元素最合适的位置
 * */
template <typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; ++i) {
        // 寻找元素arr[i]合适的插入位置
        for (int j = i; j > 0; --j) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
            } else {
                break;
            }
        }
    }
}

/*
 * 升序排序法
 * 插入排序法：改进版本，思路是将交换操作改为覆盖操作
 * */
template <typename T>
void insertSortImprovement(T* arr, int n) {
    for (int i = 1; i < n; ++i) {
        T tmp = arr[i];
        for (int j = i; j > 0; --j) {
            if (tmp < arr[j - 1]) {
                arr[j] = arr[j - 1];
            } else {
                arr[j] = tmp;
                break;
            }
        }
    }
}

int main() {
    int n = 10000;
    int* arr1 = SortHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortHelper::copyIntArr(arr1, n);
    int* arr3 = SortHelper::copyIntArr(arr1, n);
    SortHelper::testSort("selectionSort", selectionSort, arr1, n);
    SortHelper::testSort("insertionSort", insertionSort, arr2, n);
    SortHelper::testSort("insertSortImprovement", insertSortImprovement, arr3, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
}
