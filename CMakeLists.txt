cmake_minimum_required(VERSION 3.13)
project(algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(unionFind UnionFind/main.cpp UnionFind/UnionFind1.h UnionFind/UnionFindHelper.h)