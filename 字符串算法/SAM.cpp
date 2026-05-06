template<int sig = 26> //字符集大小
struct SAM {
    struct node {
        int len, link;
        array<int, sig> next;
        node(int len, int link = -1) : len(len), link(link) {
            next.fill(-1);
        }
    };
    int last;
    vector<node> tr;
    SAM() { init(); }
    void init() {
        tr.emplace_back(0, -1);
        last = 0;
    }
    int extend(int c) {
        int cur = tr.size();
        tr.emplace_back(tr[last].len + 1);
        int p = last;
        while (p != -1 && tr[p].next[c] == -1) {
            tr[p].next[c] = cur;
            p = tr[p].link;
        }
        if (p == -1) {
            tr[cur].link = 0;
        } else {
            int q = tr[p].next[c];
            if (tr[p].len + 1 == tr[q].len) {
                tr[cur].link = q;
            } else {
                int clone = tr.size();
                tr.emplace_back(tr[p].len + 1, tr[q].link);
                tr.back().next = tr[q].next;
                while (p != -1 && tr[p].next[c] == q) {
                    tr[p].next[c] = clone;
                    p = tr[p].link;
                }
                tr[q].link = tr[cur].link = clone;
            }
        }
        last = cur;
        return last;
    }
    int size() {
        return tr.size();
    }
    int len(int u) {
        return tr[u].len;
    }
    int link(int u) {
        return tr[u].link;
    }
    int next(int u, int c) {
        return tr[u].next[c];
    }
};