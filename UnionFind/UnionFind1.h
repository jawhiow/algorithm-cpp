//
// Created by LENOVO on 2020/3/17.
//

#ifndef ALGORITHM_UNIONFIND1_H
#define ALGORITHM_UNIONFIND1_H

#include <iostream>
#include <cassert>
#include "UnionFind.h"

using namespace std;

// 第一版的UnionFind，实现比较暴力，时间复杂度为O(n)，空间复杂度为O(n)
namespace UF1{

class UnionFind1 : public Uf::UnionFind{

    public:

        explicit UnionFind1(int n) : UnionFind(n) {}

        ~UnionFind1() = default;
        void unionElements(int x, int y) override {
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

        int find(int x) override {
            return id[x];
        }

        bool isConnected(int x, int y) override {
            return find(x) == find(y);
        }

    };
}


#endif //ALGORITHM_UNIONFIND1_H
