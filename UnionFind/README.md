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
第一个版本的实现非常简单，具体实现参考[这里](https://github.com/jawhiow/algorithm-cpp/blob/master/UnionFind/UnionFind1.h)，时间复杂度是O(n)，可见效率也不会太高，但却是后面实现的基础。
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

### UnionFind2 实现
在第一个版本的实现中，我们的`id`数组存储的是当前节点根节点，也就是当前节点属于哪一个组中，这个版本的实现参考[此处](https://github.com/jawhiow/algorithm-cpp/blob/master/UnionFind/UnionFind2.h)。

举个并查集的经典例子，在倚天屠龙记中，现在要判断`殷野王`和`宋青书`是不是一个门派（组）的，那么版本一中`id[殷野王]=张无忌`，`id[宋青书]=张三丰`，所以凭借`id`数组，`find`函数查找起来非常快，但是`unionElements`就很慢了，毕竟像明教这样人多势众的，如果要合并门派就要把所有人的`id`改一下。

版本二中，我们试着让`unionElements`快一点，我们让`id`改成存节点的父亲，而不是根节点。以上面的例子来说，现在`id[殷野王]=白眉鹰王`，这样存储了以后，很明显`find`函数变成了一个不断向上查找的过程，最终找到根节点，比如`id[殷野王]=白眉鹰王`，`id[白眉鹰王]=张无忌`，所以通过这样查找出了`殷野王`是张无忌这一派的。

那它使得`unionElement`快在哪了呢？比如现在我想让`殷野王`和`宋青书`合成一排，直接把`张三丰`链接到`张无忌`下面即可，所以从原来版本一中查找`武当所有弟子`变成了只需要从`宋青书`顺藤摸瓜找到张三丰即可，这样查找的次数就变成了树的高度，而我们知道大部分树的高度是远小于树节点个数的。所以虽然最坏条件下时间复杂度仍是O(n)，但也提高了效率，所以最终三个函数的实现如下：

- 首先注意：在版本二中`id`数组存储的为当前节点的父节点。
- 对于`find`函数，在这个版本中需要不断向上寻找根节点，实现如下

```cpp
// 查找过程, 查找元素x所对应的集合编号
// O(h)复杂度, h为树的高度
int find(int x) {
    while (x != id[x]) {
        x = id[x];
    }
    return x;
}
```
- 对于`unionElements`函数，这个版本中只需要把`x`的根节点合并到`y`的根节点中即可，实现如下：

```cpp
// 合并元素x和元素y所属的集合
// O(h)复杂度, h为树的高度
void unionElements(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) {
        return;
    }
    id[rootX] = rootY;
}
```
- 对于`isConnected`并无改变，不做补充了，同时`isConnected`函数我们发现所有版本的实现基本一样，可以考虑提升到基类`UnionFind`中。

最终两个版本在`main`函数中对比测试100000步：版本一耗时19秒，版本二耗时8秒，可见提升很明显。
