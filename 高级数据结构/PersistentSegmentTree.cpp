#include <bits/stdc++.h>
using namespace std;

struct PST {
    struct Node {
        int lch, rch;
        int cnt;
    };

    int n;
    vector<int> disc;
    vector<int> root;
    vector<Node> tr;

    void init(const vector<int>& a) {
        // a 下标从 1 开始
        n = (int)a.size() - 1;

        disc.clear();
        for (int i = 1; i <= n; i++) {
            disc.push_back(a[i]);
        }

        sort(disc.begin(), disc.end());
        disc.erase(unique(disc.begin(), disc.end()), disc.end());

        tr.clear();
        tr.reserve(n * 20);
        tr.push_back({0, 0, 0});

        root.assign(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            int pos = lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin() + 1;
            root[i] = update(root[i - 1], 1, disc.size(), pos);
        }
    }

    int clone(int p) {
        tr.push_back(tr[p]);
        return (int)tr.size() - 1;
    }

    int update(int p, int l, int r, int pos) {
        int cur = clone(p);
        tr[cur].cnt++;

        if (l == r) {
            return cur;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid) {
            tr[cur].lch = update(tr[p].lch, l, mid, pos);
        } else {
            tr[cur].rch = update(tr[p].rch, mid + 1, r, pos);
        }

        return cur;
    }

    // 查询版本 u - v 中的第 k 小
    int kth(int u, int v, int l, int r, int k) {
        if (l == r) {
            return l;
        }

        int mid = (l + r) >> 1;

        int left_count = tr[tr[u].lch].cnt - tr[tr[v].lch].cnt;

        if (k <= left_count) {
            return kth(tr[u].lch, tr[v].lch, l, mid, k);
        } else {
            return kth(tr[u].rch, tr[v].rch, mid + 1, r, k - left_count);
        }
    }

    // 查询 [l, r] 中第 k 小的原值
    int query_kth(int l, int r, int k) {
        int pos = kth(root[r], root[l - 1], 1, disc.size(), k);
        return disc[pos - 1];
    }

    // 查询 [l, r] 中 <= x 的数量
    int count_le(int u, int v, int l, int r, int pos) {
        if (pos <= 0) return 0;
        if (r <= pos) {
            return tr[u].cnt - tr[v].cnt;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid) {
            return count_le(tr[u].lch, tr[v].lch, l, mid, pos);
        } else {
            int left_count = tr[tr[u].lch].cnt - tr[tr[v].lch].cnt;
            return left_count + count_le(tr[u].rch, tr[v].rch, mid + 1, r, pos);
        }
    }

    int query_count_le(int l, int r, int x) {
        int pos = upper_bound(disc.begin(), disc.end(), x) - disc.begin();
        return count_le(root[r], root[l - 1], 1, disc.size(), pos);
    }
};