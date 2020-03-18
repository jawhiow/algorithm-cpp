# 并查集
本节详述了并查集这一数据结构，它常常被用来解决图中两个节点是否连接的问题。实现这一功能主要是靠内置了一个`id`数组，该数组用来存储对应节点的根节点是谁。

比如`1，2，3，4，5`都是属于根节点`1`下的，`6，7，8，9，10`都是属于根节点`6`下的，那么我们判断两个节点是否是连接的，只需要看它们存储的根节点是否相同，如`2和3`是连接的，因为`id[2]=id[3]=1`，而`4和7`则是不连接的，因为`id[4]!=id[7]`。所以借助`id`数组，我们可以很方便的判断两个节点是否连接。所以我们最终只要能够高效的维护这个数组即可。

## 代码设计
在整个实现过程中，有几次优化的过程，所以我们设计一个基类[UnionFind](https://github.com/jawhiow/algorithm-cpp/blob/master/UnionFind/UnionFind.h)，所有的优化基于继承该基类。

该基类中包含的成员变量和虚函数如下：

```cpp
int count; // 数据的个数 
int *id; // 创建一个数组存储对应的根节点

int find(int x); // 根据传入的元素，寻找对应的根节点
void unionElements(int x, int y); // 将两个元素合并到一个组中去，也就是共享同一个根节点，使得二者连接，需要注意合并是两个组之间的合并，而不只是两个元素之间的合并
bool isConnected(int x, int y); // 判断两个元素是否连接
```

## 实现和优化
### UnionFind1 实现
第一个版本的实现非常简单，具体实现参考[这里](https://github.com/jawhiow/algorithm-cpp/blob/master/UnionFind/UnionFind1.h)，时间复杂度是O(n)，可见效率也不会太高，但确实后面实现的基础。
- 对于`find`函数，直接返回数组中对应元素的值，代码如下：

```cpp
int find(int x) {
    return id[x];
}
```
- 对于`unionElements`函数，如果传入的`x和y`本身`id`相同，则直接返回，否则选择将所有等于`id[x]`的元素`id`全部置为`id[y]`，实现两个组的合并， 也就是在此处使得算法的复杂度为O(n)，具体代码如下：

```cpp
void unionElements(int x, int y){
    int xId = find(x);
    int yId = find(y);
    if (xId == yId) return;
    // 将所有为xId的全部加入yId中
    for (int i = 0; i < count; ++i) {
        if (find(i) == yId) {
            id[i] = xId;
        }
    }
```

- 最后实现的`isConnected`，直接用`find`函数判断是否连接即可，代码如下：

```cpp
bool isConnected(int x, int y) override {
	return find(x) == find(y);
}
```