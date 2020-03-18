//
// Created by LENOVO on 2020/3/18.
//

#ifndef ALGORITHM_UNIONFIND2_H
#define ALGORITHM_UNIONFIND2_H

#include <iostream>
#include <cassert>
#include "UnionFind.h"

namespace Uf2 {
class UnionFind2 : public Uf::UnionFind {

public:
    explicit UnionFind2(int n) : UnionFind(n) {}

    virtual ~UnionFind2() = default;

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
        id[rootX] = rootY;
    }

    // 查看元素x和元素y是否所属一个集合
    // O(h)复杂度, h为树的高度
    bool isConnected(int x, int y) override {
        return find(x) == find(y);
    }
};


}



#endif //ALGORITHM_UNIONFIND2_H
