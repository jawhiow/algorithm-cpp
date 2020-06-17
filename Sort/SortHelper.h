//
// Created by JT on 2020/6/15.
//

#ifndef ALGORITHM_SORTHELPER_H
#define ALGORITHM_SORTHELPER_H

#include <iostream>
#include <cassert>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

namespace SortHelper{

    // 生成n个元素的随机数组，每个数组的随机范围为[rangeL, rangeR]
    int* generateRandomArray(int n, int rangeL, int rangeR) {
        int* arr = new int[n];
        srand(time(NULL));
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % (rangeR - rangeL + 1);
        }

        return arr;
    }

    // 生成一个近乎有序的数组
    // 首先生成一个含有[0...n-1]的完全有序数组, 之后随机交换swapTimes对数据
    // swapTimes定义了数组的无序程度
    int* generateNearlyOrderedArray(int n, int swapTimes){

        int *arr = new int[n];
        for(int i = 0 ; i < n ; i ++ )
            arr[i] = i;

        srand(time(NULL));
        for( int i = 0 ; i < swapTimes ; i ++ ){
            int posx = rand()%n;
            int posy = rand()%n;
            swap( arr[posx] , arr[posy] );
        }

        return arr;
    }

    void printArr(int* arr, int n) {
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // 判断arr数组是否有序
    template<typename T>
    bool isSorted(T arr[], int n) {

        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    void testSort(const string& sortName, void(*sort)(T[], int), T arr[], int n) {
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();
        cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
        assert(isSorted(arr, n));
    }

    template <typename T>
    T* copyIntArr(T* a, int n) {
        int* arr = new int[n];
        copy(a, a + n, arr);
        return arr;
    }

}

#endif //ALGORITHM_SORTHELPER_H
