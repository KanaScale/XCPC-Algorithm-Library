# AC 自动机原理本质与经典应用场景

## 1. AC 自动机是什么

AC 自动机（Aho-Corasick Automaton）用于解决 **多模式串匹配** 问题。

它可以理解为：

```text
Trie 树 + KMP 的 fail 指针 + 自动机转移
```

如果有很多模式串，要在一个文本串中同时查找它们，逐个跑 KMP 会比较慢。AC 自动机可以把所有模式串建成一个自动机，然后只扫描文本串一次。

复杂度通常为：

```text
建自动机：O(所有模式串总长度 × 字符集大小)
匹配文本：O(文本长度 + 匹配输出数量)
```

---

## 2. AC 自动机的本质

AC 自动机的本质是：

```text
在 Trie 树上加入 fail 指针，使得匹配失败时可以跳到最长可用后缀状态。
```

普通 Trie 只能从根开始匹配。如果当前路径匹配失败，就不知道应该跳到哪里继续。

KMP 解决的是单模式串的失配跳转问题：

```text
失配时，跳到最长相等前后缀。
```

AC 自动机把这个思想推广到 Trie 上：

```text
失配时，跳到当前字符串的最长后缀状态。
```

所以可以记成：

```text
AC 自动机 = Trie 上的 KMP
```

---

## 3. Trie 部分：存储所有模式串

先把所有模式串插入 Trie。

例如模式串：

```text
he
she
his
hers
```

Trie 大致为：

```text
root
├── h
│   ├── e
│   │   └── r
│   │       └── s
│   └── i
│       └── s
└── s
    └── h
        └── e
```

每个 Trie 节点表示一个前缀字符串。

常见节点结构：

```cpp
struct Node {
    Node* son[26]{};
    Node* fail;
    Node* last;
    int len = 0;
    int cost = INT_MAX;
};
```

字段含义：

| 字段 | 含义 |
|---|---|
| `son[c]` | 当前节点沿字符 `c` 的 Trie 转移 |
| `fail` | 失配指针 |
| `last` | 最近的模式串结尾后缀节点 |
| `len` | 如果当前节点是模式串结尾，记录模式串长度 |
| `cost` | 题目附加信息，例如模式串代价 |

`last` 不是 AC 自动机必须字段，但在快速枚举后缀匹配时很有用。

---

## 4. fail 指针的含义

`fail[u]` 表示：

```text
节点 u 所代表字符串的最长真后缀，且该后缀也在 Trie 中出现。
```

例如某个节点代表字符串：

```text
abcde
```

如果 Trie 中存在后缀：

```text
cde
de
e
```

其中 `cde` 是最长的可用真后缀，那么：

```text
fail[abcde] = cde
```

这和 KMP 的 `next / pi` 数组类似。

| KMP | AC 自动机 |
|---|---|
| 一个模式串 | 多个模式串组成的 Trie |
| `next / pi` | `fail` |
| 当前匹配长度 | 当前 Trie 节点 |
| 失配后跳最长前后缀 | 失配后跳最长后缀状态 |

---

## 5. 为什么需要 fail 指针

假设文本串扫描过程中，当前状态表示已经匹配了：

```text
abcd
```

下一个字符是：

```text
x
```

但 Trie 中没有 `abcdx`。

如果没有 `fail`，只能回根重新尝试。

如果有：

```text
fail[abcd] = bcd
```

就可以直接尝试：

```text
bcd + x
```

如果还不行，再跳到 `fail[bcd]`。

这就是 AC 自动机不需要回退文本指针的原因。

---

## 6. fail 指针如何构建

`fail` 指针通常用 BFS 构建。

原因是：

```text
一个节点的 fail 依赖它父亲的 fail。
```

对于 Trie 边：

```text
cur --c--> son
```

如果 `cur->fail` 已经求好，那么：

```cpp
son->fail = cur->fail->son[c];
```

基本流程：

```text
1. root 的 fail 指向 root。
2. root 的儿子 fail 指向 root。
3. BFS 遍历 Trie。
4. 对当前节点 cur 的每个字符 c：
   - 如果有儿子 son：
       son->fail = cur->fail->son[c]
   - 如果没有儿子：
       cur->son[c] = cur->fail->son[c]
```

最后一步是补全自动机转移。补全后，匹配时可以直接：

```cpp
cur = cur->son[c];
```

不需要手动 while 跳 fail。

---

## 7. last 指针的作用

匹配到某个状态时，可能同时匹配多个模式串。

例如模式串：

```text
a
ba
cba
```

当文本扫描到 `cba` 末尾时，实际上同时匹配：

```text
cba
ba
a
```

这些模式串位于当前节点和它的 fail 链上。

如果每次都沿 fail 链暴力枚举，可能较慢。于是可以维护：

```text
last[u] = 从 fail[u] 开始，最近的一个模式串结尾节点。
```

常见构建方式：

```cpp
son->last = son->fail->len ? son->fail : son->fail->last;
```

含义：

```text
如果 fail 节点本身是模式串结尾，则 last 指向 fail；
否则继承 fail 节点的 last。
```

---

## 8. 匹配文本串

如果已经补全转移，匹配过程非常简单：

```cpp
Node* cur = root;

for (char ch : text) {
    int c = ch - 'a';
    cur = cur->son[c];

    if (cur->len) {
        // 当前节点本身是模式串结尾
    }

    for (Node* p = cur->last; p != root; p = p->last) {
        // p 是某个后缀模式串结尾
    }
}
```

如果没有补全转移，则需要写：

```cpp
while (cur != root && cur->son[c] == nullptr) {
    cur = cur->fail;
}

if (cur->son[c]) {
    cur = cur->son[c];
}
```

竞赛中更推荐补全转移，代码更简洁稳定。

---

## 9. 经典应用场景

### 9.1 多模式串匹配

题目形式：

```text
给定多个模式串和一个文本串，判断每个模式串是否出现。
```

做法：

```text
1. 插入所有模式串。
2. 构建 fail 指针。
3. 扫描文本串。
4. 遇到模式串结尾节点就标记答案。
```

---

### 9.2 统计每个模式串出现次数

题目形式：

```text
给定多个模式串和文本串，统计每个模式串出现了多少次。
```

常见做法：

```text
1. 扫描文本串，每到一个状态，该状态访问次数 +1。
2. 建 fail 树。
3. 按深度从大到小，把节点计数累加到 fail 父亲。
4. 每个模式串结尾节点的计数就是出现次数。
```

为什么要沿 fail 累加？

```text
如果一个长串出现，那么它的后缀模式串也可能出现。
fail 指针正好描述这种后缀关系。
```

---

### 9.3 敏感词检测

题目形式：

```text
给定很多禁词，判断文本中是否出现任意禁词。
```

做法：

```text
1. 把禁词插入 AC 自动机。
2. 扫描文本。
3. 如果当前状态或 last 链上有模式串结尾，说明出现禁词。
```

这是 AC 自动机最典型的工程应用。

---

### 9.4 禁止出现某些子串的字符串 DP

题目形式：

```text
求长度为 n 的字符串数量，要求不包含任何禁用模式串。
```

做法：

```text
1. 把禁串插入 AC 自动机。
2. 标记危险节点：自己是禁串结尾，或者 fail 链上存在禁串结尾。
3. 在 AC 自动机上做 DP。
```

状态：

```text
dp[pos][state]
```

表示：

```text
已经构造了 pos 个字符，当前自动机状态为 state 的方案数。
```

转移：

```cpp
for (int pos = 0; pos < n; pos++) {
    for (int u = 0; u < tot; u++) {
        if (bad[u]) continue;

        for (int c = 0; c < 26; c++) {
            int v = nxt[u][c];
            if (!bad[v]) {
                dp[pos + 1][v] += dp[pos][u];
            }
        }
    }
}
```

---

### 9.5 最短包含所有模式串的字符串

如果模式串数量较少，可以用：

```text
AC 自动机 + 状压 BFS
```

状态：

```text
(state, mask)
```

其中：

```text
state = 当前自动机节点
mask = 已经包含了哪些模式串
```

转移：

```text
枚举下一个字符 c
next_state = go(state, c)
next_mask = mask | output[next_state]
```

第一次到达 `mask = full` 的状态，就是最短答案。

---

### 9.6 AC 自动机 + 矩阵快速幂

题目形式：

```text
求长度为 n 的字符串数量，且不包含禁串，n 非常大。
```

如果普通 DP 的 `O(n × 状态数 × 字符集)` 太慢，可以把状态转移矩阵化，然后矩阵快速幂。

---

## 10. 常见易错点

### 10.1 root 的 fail 应该指向 root

```cpp
root->fail = root;
root->last = root;
```

这样可以避免空指针。

### 10.2 root 的空儿子补成 root

```cpp
for (auto &son : root->son) {
    if (son == nullptr) son = root;
}
```

这样匹配时 `cur = cur->son[c]` 一定合法。

### 10.3 fail 必须 BFS 构建

因为儿子的 fail 依赖父亲的 fail。

### 10.4 一个节点可能对应多个模式串

如果有重复模式串，或者多个模式串在同一节点结束，最好用：

```cpp
vector<int> ids;
```

而不是只存一个 `id`。

### 10.5 不要漏掉 fail / last 链上的后缀模式串

匹配到当前节点时，它的后缀节点也可能是模式串结尾。

---

## 11. 数组版 AC 自动机模板

```cpp
#include <bits/stdc++.h>
using namespace std;

struct ACAutomaton {
    static const int SIG = 26;

    struct Node {
        int son[SIG];
        int fail;
        int cnt;
        bool bad;

        Node() {
            memset(son, 0, sizeof son);
            fail = 0;
            cnt = 0;
            bad = false;
        }
    };

    vector<Node> tr;

    ACAutomaton() {
        tr.push_back(Node()); // root = 0
    }

    int insert(const string& s) {
        int u = 0;

        for (char ch : s) {
            int c = ch - 'a';
            if (!tr[u].son[c]) {
                tr[u].son[c] = tr.size();
                tr.push_back(Node());
            }
            u = tr[u].son[c];
        }

        tr[u].cnt++;
        return u;
    }

    void build() {
        queue<int> q;

        for (int c = 0; c < SIG; c++) {
            int v = tr[0].son[c];
            if (v) {
                tr[v].fail = 0;
                q.push(v);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            tr[u].bad = tr[u].bad || tr[tr[u].fail].bad;

            for (int c = 0; c < SIG; c++) {
                int v = tr[u].son[c];
                if (v) {
                    tr[v].fail = tr[tr[u].fail].son[c];
                    q.push(v);
                } else {
                    tr[u].son[c] = tr[tr[u].fail].son[c];
                }
            }
        }
    }
};
```

如果要标记禁串：

```cpp
int terminal = ac.insert(pattern);
ac.tr[terminal].bad = true;
```

`build()` 后，如果一个节点的 fail 链上存在禁串结尾，它也会被标记为危险状态。

---

## 12. 总结

AC 自动机的核心：

```text
Trie 存多个模式串；
fail 指针负责失配后跳到最长后缀状态；
补全转移后，匹配文本时每个字符只处理一次。
```

经典应用：

```text
多模式串匹配
敏感词检测
模式串出现次数统计
避免禁串的字符串 DP
AC 自动机 + 状压 BFS
AC 自动机 + 矩阵快速幂
AC 自动机 + 图论 DP
```

一句话记忆：

```text
KMP 解决一个模式串；Trie 存多个模式串；AC 自动机 = Trie + KMP 的 fail 思想。
```
