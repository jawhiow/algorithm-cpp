//
// Created by LENOVO on 2020/3/18.
//

#ifndef ALGORITHM_UNIONFIND_H
#define ALGORITHM_UNIONFIND_H


namespace Uf {
    class UnionFind {

    protected:
        int count; // 数据的个数
        int *id; // 创建一个数组存储

    public:
        explicit UnionFind(int n) {
            id = new int[n];
            count = n;
            for (int i = 0; i < n; ++i) {
                id[i] = i;
            }
        }

        ~UnionFind(){
            delete[] id;
        }

        virtual int find(int x) = 0;
        virtual void unionElements(int x, int y) = 0;
        virtual bool isConnected(int x, int y) = 0;
    };
}


#endif //ALGORITHM_UNIONFIND_H
