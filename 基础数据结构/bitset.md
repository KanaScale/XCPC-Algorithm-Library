# C++ `bitset` 用法与经典应用场景

## 1. `bitset` 是什么

`std::bitset<N>` 是 C++ 标准库中用于维护固定长度二进制位集合的数据结构。

它可以理解为一个长度为 `N` 的 `0/1` 数组，但底层按机器字压缩存储，因此支持非常快的按位运算。

```cpp
#include <bitset>
using namespace std;

bitset<1000> b;
```

注意：

```cpp
bitset<N>
```

中的 `N` 必须是编译期常量，不能是运行时输入的变量。

正确：

```cpp
const int MAXN = 100005;
bitset<MAXN> b;
```

错误：

```cpp
int n;
cin >> n;
bitset<n> b; // 错误，n 不是编译期常量
```

如果需要运行时动态长度，一般使用：

```cpp
vector<unsigned long long>
```

手写动态 bitset。

---

## 2. 基本声明与初始化

### 2.1 默认初始化

```cpp
bitset<8> b;
```

默认所有位都是 `0`：

```text
00000000
```

### 2.2 用整数初始化

```cpp
bitset<8> b(13);
cout << b << '\n';
```

输出：

```text
00001101
```

因为：

```text
13 = 8 + 4 + 1 = 1101₂
```

### 2.3 用字符串初始化

```cpp
bitset<8> b(string("1011"));
cout << b << '\n';
```

输出：

```text
00001011
```

字符串右端对应低位。

---

## 3. 位下标规则

`bitset` 的下标从 `0` 开始。

```cpp
bitset<8> b;
b.set(0);
b.set(3);
cout << b << '\n';
```

输出：

```text
00001001
```

含义：

```text
b[0] 是最低位，也就是最右边那一位
b[7] 是最高位，也就是最左边那一位
```

所以：

```cpp
b[0] = 1;
```

影响的是输出中的最右边一位。

---

## 4. 常用函数

## 4.1 `set()`：置为 1

### 全部置为 1

```cpp
bitset<8> b;
b.set();
cout << b << '\n';
```

输出：

```text
11111111
```

### 指定位置置为 1

```cpp
bitset<8> b;
b.set(3);
cout << b << '\n';
```

输出：

```text
00001000
```

### 指定位置设为某个值

```cpp
b.set(3, 0); // 第 3 位设为 0
b.set(3, 1); // 第 3 位设为 1
```

---

## 4.2 `reset()`：置为 0

### 全部置为 0

```cpp
bitset<8> b;
b.set();
b.reset();
cout << b << '\n';
```

输出：

```text
00000000
```

### 指定位置置为 0

```cpp
bitset<8> b;
b.set();
b.reset(2);
cout << b << '\n';
```

输出：

```text
11111011
```

---

## 4.3 `flip()`：翻转

### 全部翻转

```cpp
bitset<8> b(string("00001111"));
b.flip();
cout << b << '\n';
```

输出：

```text
11110000
```

### 指定位置翻转

```cpp
bitset<8> b;
b.flip(2);
cout << b << '\n';
```

输出：

```text
00000100
```

---

## 4.4 `test(pos)`：判断某位是否为 1

```cpp
bitset<8> b;
b.set(3);

if (b.test(3)) {
    cout << "bit 3 is 1\n";
}
```

等价于：

```cpp
if (b[3]) {
    ...
}
```

区别是：

```cpp
test(pos)
```

会检查越界，越界时抛异常；而 `operator[]` 通常不做安全检查。

---

## 4.5 `count()`：统计 1 的个数

```cpp
bitset<8> b(string("10101100"));
cout << b.count() << '\n';
```

输出：

```text
4
```

常用于统计集合大小。

---

## 4.6 `any()`：是否存在 1

```cpp
bitset<8> b;
cout << b.any() << '\n';

b.set(3);
cout << b.any() << '\n';
```

输出：

```text
0
1
```

---

## 4.7 `none()`：是否全是 0

```cpp
bitset<8> b;
cout << b.none() << '\n';

b.set(3);
cout << b.none() << '\n';
```

输出：

```text
1
0
```

---

## 4.8 `all()`：是否全是 1

`all()` 是 C++11 引入的。

```cpp
bitset<8> b;
b.set();
cout << b.all() << '\n';
```

输出：

```text
1
```

---

## 4.9 `size()`：返回 bitset 长度

```cpp
bitset<8> b;
cout << b.size() << '\n';
```

输出：

```text
8
```

---

## 4.10 `to_string()`：转成字符串

```cpp
bitset<8> b(13);
string s = b.to_string();
cout << s << '\n';
```

输出：

```text
00001101
```

---

## 4.11 `to_ulong()` / `to_ullong()`：转成整数

```cpp
bitset<8> b(string("00001101"));
cout << b.to_ulong() << '\n';
cout << b.to_ullong() << '\n';
```

输出：

```text
13
13
```

注意：如果 `bitset` 表示的数超过目标整数类型范围，会抛出异常。

---

## 5. 常用运算符

## 5.1 按位与 `&`

```cpp
bitset<8> a(string("11001100"));
bitset<8> b(string("10101010"));

cout << (a & b) << '\n';
```

输出：

```text
10001000
```

常用于求两个集合的交集。

---

## 5.2 按位或 `|`

```cpp
bitset<8> a(string("11001100"));
bitset<8> b(string("10101010"));

cout << (a | b) << '\n';
```

输出：

```text
11101110
```

常用于求两个集合的并集。

---

## 5.3 按位异或 `^`

```cpp
bitset<8> a(string("11001100"));
bitset<8> b(string("10101010"));

cout << (a ^ b) << '\n';
```

输出：

```text
01100110
```

常用于求不同位、状态翻转等。

---

## 5.4 按位取反 `~`

```cpp
bitset<8> a(string("11001100"));
cout << (~a) << '\n';
```

输出：

```text
00110011
```

---

## 5.5 左移 `<<` 和右移 `>>`

```cpp
bitset<8> b(string("00001101"));

cout << (b << 1) << '\n';
cout << (b >> 1) << '\n';
```

输出：

```text
00011010
00000110
```

左移相当于把集合中的位置整体加上偏移量。  
右移相当于把集合中的位置整体减去偏移量。

这是 bitset 优化 DP 的核心操作之一。

---

## 5.6 复合赋值运算

```cpp
bitset<8> a, b;

a |= b;
a &= b;
a ^= b;
a <<= 2;
a >>= 2;
```

这些写法会直接修改 `a`。

---

## 6. `bitset` 表示集合

可以把 `bitset` 看作一个集合：

```text
第 i 位为 1  <=>  集合中存在元素 i
```

例如：

```cpp
bitset<10> s;

s.set(2);
s.set(5);
s.set(7);
```

表示集合：

```text
{2, 5, 7}
```

集合操作：

```cpp
A | B  // 并集
A & B  // 交集
A ^ B  // 对称差
~A     // 补集，限制在 bitset 长度内
```

集合大小：

```cpp
A.count()
```

判断是否有交集：

```cpp
if ((A & B).any()) {
    // 有交集
}
```

---

# 7. 经典应用场景

## 7.1 可达性 DP

### 问题

给定若干数字，判断哪些和可以被凑出来。

### 普通 DP

```cpp
for (int x : a) {
    for (int s = S; s >= x; s--) {
        dp[s] |= dp[s - x];
    }
}
```

### bitset 优化

```cpp
bitset<MAXS> dp;
dp[0] = 1;

for (int x : a) {
    dp |= (dp << x);
}
```

含义：

```text
原来能凑出 s
加入 x 后，就能凑出 s + x
```

所以左移 `x` 位。

完整例子：

```cpp
const int MAXS = 100005;
bitset<MAXS> dp;

dp[0] = 1;

for (int x : a) {
    dp |= dp << x;
}

if (dp[target]) {
    cout << "YES\n";
} else {
    cout << "NO\n";
}
```

---

## 7.2 01 背包可行性优化

如果只关心某个容量是否可达，而不关心最大价值，可以用 bitset。

```cpp
bitset<MAXW> dp;
dp[0] = 1;

for (int w : weight) {
    dp |= dp << w;
}
```

最后：

```cpp
for (int s = W; s >= 0; s--) {
    if (dp[s]) {
        cout << s << '\n';
        break;
    }
}
```

表示不超过 `W` 的最大可达重量。

---

## 7.3 多重背包的可达性

如果每种物品数量不多，可以二进制拆分后配合 bitset。

```cpp
bitset<MAXS> dp;
dp[0] = 1;

for (auto [w, cnt] : items) {
    int k = 1;
    while (cnt > 0) {
        int take = min(k, cnt);
        dp |= dp << (take * w);
        cnt -= take;
        k <<= 1;
    }
}
```

---

## 7.4 图的邻接矩阵优化

对于稠密图，可以用 bitset 存每个点的邻接集合。

```cpp
const int MAXN = 2005;
bitset<MAXN> adj[MAXN];
```

如果有边 `u -> v`：

```cpp
adj[u].set(v);
```

判断两个点是否有公共邻居：

```cpp
if ((adj[u] & adj[v]).any()) {
    // 有公共邻居
}
```

公共邻居数量：

```cpp
int cnt = (adj[u] & adj[v]).count();
```

这比逐个枚举邻居快很多。

---

## 7.5 传递闭包 Floyd 优化

普通 Floyd 求传递闭包是 `O(n^3)`。

用 bitset 可以优化为约：

```text
O(n^3 / 64)
```

模板：

```cpp
const int MAXN = 2005;
bitset<MAXN> reach[MAXN];

for (int i = 0; i < n; i++) {
    reach[i][i] = 1;
}

for (auto [u, v] : edges) {
    reach[u][v] = 1;
}

for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        if (reach[i][k]) {
            reach[i] |= reach[k];
        }
    }
}
```

含义：

```text
如果 i 能到 k，那么 i 能到达的点集合可以并上 k 能到达的点集合。
```

---

## 7.6 DAG 可达点集合 DP

如果图是 DAG，可以倒序做：

```cpp
for (int u = n; u >= 1; u--) {
    reach[u].set(u);
    for (int v : g[u]) {
        reach[u] |= reach[v];
    }
}
```

最后：

```cpp
reach[u].count()
```

就是从 `u` 出发能到达的点数。

如果编号不保证拓扑序，需要先拓扑排序，再逆拓扑序 DP。

---

## 7.7 字符串匹配中的字符位置集合

可以为每个字符维护一个 bitset，表示它在哪些位置出现。

```cpp
bitset<MAXN> pos[26];

for (int i = 0; i < n; i++) {
    pos[s[i] - 'a'].set(i);
}
```

例如查询某个字符在区间中是否出现，可以结合位移或前缀结构处理。

在一些字符串 DP 或自动机优化中，也会使用字符位置 bitset 加速匹配。

---

## 7.8 集合交并快速统计

如果每个对象有一个属性集合，可以用 bitset 表示。

例如：

```cpp
bitset<MAXM> feature[MAXN];
```

两个对象共同属性数量：

```cpp
int common = (feature[i] & feature[j]).count();
```

是否互斥：

```cpp
if ((feature[i] & feature[j]).none()) {
    // 没有共同属性
}
```

是否有交集：

```cpp
if ((feature[i] & feature[j]).any()) {
    // 存在共同属性
}
```

---

## 7.9 状态压缩 DP 中的小规模集合

如果集合大小不大，通常用整数位运算：

```cpp
int mask;
```

如果集合大小较大，比如 `1000`、`10000`，就可以用：

```cpp
bitset<MAXN>
```

例如维护某个状态能到达的一批编号：

```cpp
dp[u] |= dp[v];
```

---

## 7.10 本题相关：权值集合 DP

如果从某个点出发能到达若干后继，并且要求统计不同权值数量，可以用 bitset 表示权值集合。

```cpp
const int MAXN = 40005;
bitset<MAXN> dp[MAXN];

for (int i = n; i >= 1; i--) {
    dp[i].set(c[i]);

    if (i + c[i] <= n) {
        dp[i] |= dp[i + c[i]];
    }

    if (2 * i <= n) {
        dp[i] |= dp[2 * i];
    }

    ans = max(ans, (int)dp[i].count());
}
```

含义：

```text
dp[i] = 从 i 出发可能经过的所有权值集合
```

---

# 8. 时间复杂度理解

`bitset` 的按位运算不是逐位慢慢处理，而是按机器字处理。

例如：

```cpp
A |= B;
```

如果 `bitset` 长度是 `N`，复杂度大约是：

```text
O(N / 64)
```

因为一个 `unsigned long long` 通常可以同时处理 `64` 位。

所以 bitset 的常见优势是把：

```text
O(N)
```

优化成：

```text
O(N / 64)
```

在 `N` 比较大、操作次数很多时非常有用。

---

# 9. 常见易错点

## 9.1 `N` 必须是编译期常量

```cpp
int n;
cin >> n;
bitset<n> b; // 错误
```

正确：

```cpp
const int MAXN = 100005;
bitset<MAXN> b;
```

---

## 9.2 下标 0 是最低位

```cpp
bitset<8> b;
b.set(0);
cout << b << '\n';
```

输出：

```text
00000001
```

不是：

```text
10000000
```

---

## 9.3 左移后超出范围的位会被丢弃

```cpp
bitset<8> b(string("10000000"));
cout << (b << 1) << '\n';
```

输出：

```text
00000000
```

最高位被移出范围后直接丢弃。

---

## 9.4 `~b` 会翻转全部长度内的位

```cpp
bitset<8> b(string("00001111"));
cout << ~b << '\n';
```

输出：

```text
11110000
```

如果你的有效范围只到 `n`，但 `bitset` 开到了 `MAXN`，取反后 `n` 以后的无效位也会变成 `1`。

这种情况下需要手动清掉无效位，或者避免直接用 `~`。

---

## 9.5 大量 `bitset` 可能占很多内存

例如：

```cpp
bitset<40005> dp[40005];
```

空间大约是：

```text
40005 * 40005 bits ≈ 200 MB
```

如果内存限制是 `128 MB`，可能会超内存。

可以改成：

```cpp
vector<unsigned long long>
```

手写动态 bitset，或压缩值域。

---

# 10. 常用模板汇总

## 10.1 子集和可达性

```cpp
const int MAXS = 100005;
bitset<MAXS> dp;

dp[0] = 1;

for (int x : a) {
    dp |= dp << x;
}
```

---

## 10.2 图可达性传递闭包

```cpp
const int MAXN = 2005;
bitset<MAXN> reach[MAXN];

for (int i = 0; i < n; i++) {
    reach[i][i] = 1;
}

for (auto [u, v] : edges) {
    reach[u][v] = 1;
}

for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        if (reach[i][k]) {
            reach[i] |= reach[k];
        }
    }
}
```

---

## 10.3 DAG 可达集合 DP

```cpp
for (int u : reverse_topo_order) {
    reach[u].set(u);
    for (int v : g[u]) {
        reach[u] |= reach[v];
    }
}
```

---

## 10.4 集合交集统计

```cpp
int common = (A & B).count();
```

---

## 10.5 判断两个集合是否有交集

```cpp
if ((A & B).any()) {
    cout << "intersect\n";
}
```

---

# 11. 总结

`bitset` 最适合用于：

```text
1. 状态是 0/1 的集合；
2. 需要频繁做集合并、交、异或；
3. 需要快速统计集合大小；
4. 可以接受固定最大长度；
5. 普通 O(n) 转移可以变成 O(n / 64)。
```

最常见的思考方式：

```text
把“集合”压成一个 bitset，
把“枚举元素”变成“整体按位运算”。
```

一旦题目里出现：

```text
可达集合、不同值集合、子集和、交集数量、传递闭包、DAG 可达点
```

就可以优先考虑 `bitset` 优化。
