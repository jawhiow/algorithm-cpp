//
// Created by LENOVO on 2020/3/17.
//

#ifndef ALGORITHM_UNIONFIND1_H
#define ALGORITHM_UNIONFIND1_H

#include <iostream>
#include <cassert>

using namespace std;

// 第一版的UnionFind，实现比较暴力，时间复杂度为O(n)，空间复杂度为O(n)

namespace UF1{

    class UnionFind{

    private:
        int *id; // 创建一个数组存储
        int count; // 数据的个数

    public:
        UnionFind(int n) {
            count = n;
            id = new int[n];

            // 初始化数据，每个id[i]=i，也就是指向自己
            for (int i = 0; i < n; ++i) {
                id[i] = i;
            }
        }

        ~UnionFind(){
            delete[] id;
        }

        void unionElements(int x, int y) {
            int xId = find(x);
            int yId = find(y);

            if (xId == yId) return;

            // 将所有为xId的全部加入yId中
            for (int i = 0; i < count; ++i) {
                if (find(i) == yId) {
                    id[i] = xId;
                }
            }
        }

        int find(int x) {
            return id[x];
        }

        bool isConnected(int x, int y) {
            return find(x) == find(y);
        }

    };
}


#endif //ALGORITHM_UNIONFIND1_H
