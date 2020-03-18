//
// Created by LENOVO on 2020/3/17.
//

#ifndef ALGORITHM_UNIONFINDHELPER_H
#define ALGORITHM_UNIONFINDHELPER_H

#include <iostream>
#include <ctime>
#include "UnionFind1.h"

namespace UnionFindTestHelper {

    void testUf1(int n) {
        srand(time(nullptr));
        UF1::UnionFind uf = UF1::UnionFind(n);
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

        cout << "UF1, " << 2 * n << "ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
    }
}



#endif //ALGORITHM_UNIONFINDHELPER_H
