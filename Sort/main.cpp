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

/*
 * 升序排序法
 * 冒泡排序法: 相邻元素进行交换，每次确定一个位置
 * */
template <typename T>
void bubbleSort(T* arr, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


/*
 * 升序排序法
 * 冒泡排序法改进: 用一个变量记录最后一次的交换位置,在此之后的元素在下一轮扫描中均不考虑
 * 此改进，对于完全有序的数组，冒泡排序法也将成为O(n)级别的算法
 * */
template <typename T>
void bubbleSortImprovement(T* arr, int n) {
    int newn = n;
    while (newn > 0) {
        newn = 0;
        for (int j = 1; j < n; ++j) {
            if (arr[j - 1] > arr[j]) {
                swap(arr[j - 1], arr[j]);
                newn = j;
            }
        }
        n = newn;
    }
}

/*将arr[left...mid]和arr[mid+1...right]归并成一个有序数组*/
template <typename T>
void __merge(T* arr, int left, int mid, int right) {
    int n = right - left + 1;
    T* tmpArr = new T[n];
    for (int i = left; i <= right; ++i) {
        tmpArr[i - left] = arr[i];
    }

    int i = left, j = mid + 1;
    for (int k = left; k <= right; ++k) {
        if (i > mid) {
            // 表示[mid+1,right]数组还没遍历完成
            arr[k] = tmpArr[j - left];
            j++;
        } else if (j > right) {
            arr[k] = tmpArr[i - left];
            i++;
        } else if (tmpArr[i - left] < tmpArr[j - left]) {
            arr[k] = tmpArr[i - left];
            i++;
        } else {
            arr[k] = tmpArr[j - left];
            j++;
        }
    }
    delete[] tmpArr;
}

/*递归使用归并排序，对arr[left...right]范围的数组进行排序*/
template <typename T>
void __mergeSort(T *arr, int left, int right) {
    // left，right划分的arr区间为[left, right]
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    // 分治
    __mergeSort(arr, left, mid);
    __mergeSort(arr, mid + 1, right);
    // 归并
    __merge(arr, left, mid, right);

}

/*归并排序循环版*/
template <typename T>
void __mergeSort(T* arr, int n) {
    for (int i = 2; i < n; i *= 2) {
        int j = 0;
        while (j < n) {
            int left = j;
            int right = j + i - 1;
            int mid = left + i / 2 - 1;
            if (right >= n) {
                right = n - 1;
            }
            __merge(arr, left, mid, right);
            j = right + 1;
        }
        // 当i < n 但是 i * 2 > n，说明剩最后两组未归并
        if (i < n && i * 2 > n) {
            __merge(arr, 0, i - 1, n - 1);
        }
    }
}

/*
 * 归并排序
 * */
template <typename T>
void mergeSort(T* arr, int n) {
    // 递归版归并排序
    //__mergeSort(arr, 0, n - 1);
    // 循环版归并排序
    __mergeSort(arr, n);
}

void testBasicSort(int n) {

    // 测试一：随机数组测试各算法性能
    int* arr1 = SortHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortHelper::copyIntArr(arr1, n);
    int* arr3 = SortHelper::copyIntArr(arr1, n);
    int* arr4 = SortHelper::copyIntArr(arr1, n);
    int* arr5 = SortHelper::copyIntArr(arr1, n);
    SortHelper::testSort("selectionSort", selectionSort, arr1, n);
    SortHelper::testSort("insertionSort", insertionSort, arr2, n);
    SortHelper::testSort("insertSortImprovement", insertSortImprovement, arr3, n);
    SortHelper::testSort("bubbleSort", bubbleSort, arr4, n);
    SortHelper::testSort("bubbleSortImprovement", bubbleSortImprovement, arr5, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    cout << endl;

    // 测试二：近乎有序的数组测试各算法性能
    int swapTimes = 100;
    cout << "test for nearly ordered array : " << endl;
    arr1 = SortHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortHelper::copyIntArr(arr1, n);
    arr3 = SortHelper::copyIntArr(arr1, n);
    arr4 = SortHelper::copyIntArr(arr1, n);
    arr5 = SortHelper::copyIntArr(arr1, n);
    SortHelper::testSort("selectionSort", selectionSort, arr1, n);
    SortHelper::testSort("insertionSort", insertionSort, arr2, n);
    SortHelper::testSort("insertSortImprovement", insertSortImprovement, arr3, n);
    SortHelper::testSort("bubbleSort", bubbleSort, arr4, n);
    SortHelper::testSort("bubbleSortImprovement", bubbleSortImprovement, arr5, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
}

void testAdvanceSort(int n) {
    int* arr1 = SortHelper::generateRandomArray(n, 0, n);
    SortHelper::testSort("mergeSort", mergeSort, arr1, n);

    delete[] arr1;
}

int main() {
    int n = 1000000;
    // 基础排序测试
    // testBasicSort(n);
    // 高级排序测试
    testAdvanceSort(n);

    return 0;
}
