//
// Created by LENOVO on 2020/3/19.
//

#ifndef ALGORITHM_UNIONFIND5_H
#define ALGORITHM_UNIONFIND5_H

#include "UnionFind.h"
#include <cassert>

namespace Uf5 {
    class UnionFind5 : public Uf::UnionFind {

    private:
        int* rank; // 创建一个rank数组来存储树的高度

    public:
        explicit UnionFind5(int n) : UnionFind(n) {
            rank = new int[count];
            for (int i = 0; i < count; ++i) {
                rank[i] = 1; // 初始化树的高度为1
            }
        }

        virtual ~UnionFind5() {
            delete[] rank;
        }

        int find(int x) override {
            assert( x >= 0 && x < count );
            // 第一个版本路径压缩的优化
            /*while (x != id[x]) {
                // x的父亲指向父亲的父亲
                id[x] = id[id[x]];
                x = id[x];
            }
            return x;
             */
            // 第二个版本的路径压缩的优化
            // 使得所有节点都直接挂到根节点下面，树只有两层
            if (x != id[x]) {
                id[x] = find(id[x]);
            }
            return id[x];
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
#endif //ALGORITHM_UNIONFIND5_H
