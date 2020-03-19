//
// Created by LENOVO on 2020/3/19.
//

#ifndef ALGORITHM_UNIONFIND4_H
#define ALGORITHM_UNIONFIND4_H

#include "UnionFind.h"
#include <cassert>

namespace Uf4 {
class UnionFind4 : public Uf::UnionFind {

private:
    int* rank; // 创建一个rank数组来存储树的高度

public:
    explicit UnionFind4(int n) : UnionFind(n) {
        rank = new int[count];
        for (int i = 0; i < count; ++i) {
            rank[i] = 1; // 初始化树的高度为1
        }
    }

    virtual ~UnionFind4() {
        delete[] rank;
    }

    int find(int x) override {
        assert( x >= 0 && x < count );
        while (x != id[x]) {
            x = id[x];
        }
        return x;
    }

    void unionElements(int x, int y) override {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (rank[rootX] > rank[rootY]) {
            // 当x的高度比y大，则需要把y链接到x上
            id[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            id[rootX] = rootY;
        } else{
            // 两者相等，则随机选择一个链接，并增加对应高度
            id[rootX] = rootY; // 将x链接到y上，则y的高度需要增加
            rank[rootY] ++;
        }
    }

    bool isConnected(int x, int y) override {
        return find(x) == find(y);
    }

};
}

#endif //ALGORITHM_UNIONFIND4_H
