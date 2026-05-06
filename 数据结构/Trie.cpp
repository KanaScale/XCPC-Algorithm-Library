// N 是你能插入的所有单词长度的总和上限
// 如果题目最多有 10^5 个字符，这里就开 100005
const int N = 100005; 

class Trie {
private:
    // son[p][u] 表示节点 p 的第 u 个子节点是谁 (存储的是节点编号)
    int son[N][26]; 
    bool isEnd[N];
    int clk; // 节点分配器，0 号节点同时充当 根节点(root) 和 空节点(null)

public:
    Trie() {
        // 如果只会创建一个 Trie 实例，不用 memset 也可以（全局变量默认是 0）
        // 如果在多组测试数据中重复使用，需要清空
        memset(son, 0, sizeof(son));
        memset(isEnd, 0, sizeof(isEnd));
        clk = 0; 
    }

    int find(string word) {
        int p = 0; // 从根节点 0 开始
        for (char c : word) {
            int u = c - 'a';
            if (son[p][u] == 0) return 0; // 如果指向 0，说明没有这个子节点
            p = son[p][u]; // 往下走
        }
        return isEnd[p] ? 2 : 1;
    }

    void insert(string word) {
        int p = 0; 
        for (char c : word) {
            int u = c - 'a';
            if (son[p][u] == 0) {
                // 如果没有子节点，就分配一个新编号 ++clk 给它
                son[p][u] = ++clk; 
            }
            p = son[p][u];
        }
        isEnd[p] = true;
    }

    bool search(string word) {
        return find(word) == 2;
    }

    bool startsWith(string prefix) {
        return find(prefix) != 0;
    }
};