cmake_minimum_required(VERSION 3.13)
project(algorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(unionFind UnionFind/main.cpp UnionFind/UnionFind1.h UnionFind/UnionFindHelper.h UnionFind/UnionFind.h UnionFind/UnionFind2.h UnionFind/UnionFind3.h UnionFind/UnionFind4.h UnionFind/UnionFind5.h)
add_executable(sort Sort/main.cpp Sort/SortHelper.h)