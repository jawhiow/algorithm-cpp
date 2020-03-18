//
// Created by LENOVO on 2020/3/18.
//

#ifndef ALGORITHM_UNIONFIND3_H
#define ALGORITHM_UNIONFIND3_H

#include <iostream>
#include <cassert>
#include "UnionFind.h"



namespace Uf3 {
    class UnionFind3 : public Uf::UnionFind {
    private:
        int *sz; // sz[i]表示以i为根的集合中元素个数

    public:
        explicit UnionFind3(int n) : UnionFind(n) {
            this->sz = new int[n];
            for (int i = 0; i < n; ++i) {
                sz[i] = 1;
            }
        }

        virtual ~UnionFind3(){
            delete[] sz;
        }

        // 查找过程, 查找元素x所对应的集合编号
        // O(h)复杂度, h为树的高度
        int find(int x) override {
            assert(x >= 0 && x < count);
            while (x != id[x]) {
                x = id[x];
            }
            return x;
        }

        // 合并元素x和元素y所属的集合
        // O(h)复杂度, h为树的高度
        void unionElements(int x, int y) override {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) {
                return;
            }
            // 希望将数量少的合并到数量大的上
            if (sz[rootX] > sz[rootY]) {
                // 将rootY合并到rootX中
                id[rootY] = rootX;
                sz[rootX] += sz[rootY];
            } else{
                id[rootX] = rootY;
                sz[rootY] += sz[rootX];
            }
        }

        // 查看元素x和元素y是否所属一个集合
        // O(h)复杂度, h为树的高度
        bool isConnected(int x, int y) override {
            return find(x) == find(y);
        }
    };


}

#endif //ALGORITHM_UNIONFIND3_H
