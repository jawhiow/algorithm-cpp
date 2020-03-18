//
// Created by LENOVO on 2020/3/17.
//

#ifndef ALGORITHM_UNIONFINDHELPER_H
#define ALGORITHM_UNIONFINDHELPER_H

#include <iostream>
#include <ctime>
#include "UnionFind1.h"
#include "UnionFind2.h"
#include "UnionFind.h"

namespace UnionFindTestHelper {
    void testUf(int n, Uf::UnionFind &uf);

    void testUf1 (int n) {
        UF1::UnionFind1 uf1 = UF1::UnionFind1(n);
        Uf::UnionFind &uf = uf1;
        testUf(n, uf);
    }

    void testUf2 (int n) {
        Uf2::UnionFind2 uf2 = Uf2::UnionFind2(n);
        Uf::UnionFind &uf = uf2;
        testUf(n, uf);
    }

    void testUf(int n, Uf::UnionFind &uf) {
        srand(time(nullptr));
        time_t startTime = clock();

        // 进行n次操作，每次随机选择两个元素进行合并操作
        for (int i = 0; i < n; ++i) {
            int a = rand() % n;
            int b = rand() % n;
            uf.unionElements(a, b);
        }

        // 进行n次操作，每次随机选择两个元素，查询他们是否连接
        for (int j = 0; j < n; ++j) {
            int a = rand() % n;
            int b = rand() % n;
            uf.isConnected(a, b);
        }

        time_t endTime = clock();

        cout << "UF, " << 2 * n << "ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
    }
}



#endif //ALGORITHM_UNIONFINDHELPER_H
