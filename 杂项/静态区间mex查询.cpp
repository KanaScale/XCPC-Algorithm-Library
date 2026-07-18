//值域主席树，维护每个值最早出现下标
//查询[L,R] mex，即在R前缀对应版本中，线段树二分找到最小的x，使得last[x] < L
struct StaticRangeMex {
    struct Node {
        int lch, rch;
        int mn; // 当前区间内 last[x] 的最小值
    };

    int n;
    vector<int> root;
    vector<Node> tr;

    StaticRangeMex() {}

    StaticRangeMex(const vector<int>& a) {
        build(a);
    }

    int new_node() {
        tr.push_back({0, 0, 0});
        return (int)tr.size() - 1;
    }

    int build_empty(int l, int r) {
        int p = new_node();

        if (l == r) {
            tr[p].mn = 0;
            return p;
        }

        int mid = (l + r) >> 1;

        tr[p].lch = build_empty(l, mid);
        tr[p].rch = build_empty(mid + 1, r);
        tr[p].mn = 0;

        return p;
    }

    int update(int pre, int l, int r, int pos, int val) {
        int p = new_node();
        tr[p] = tr[pre];

        if (l == r) {
            tr[p].mn = val;
            return p;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid) {
            tr[p].lch = update(tr[pre].lch, l, mid, pos, val);
        } else {
            tr[p].rch = update(tr[pre].rch, mid + 1, r, pos, val);
        }

        tr[p].mn = min(tr[tr[p].lch].mn, tr[tr[p].rch].mn);

        return p;
    }

    // 找最小的 x，使得 last[x] < L
    int query_mex(int p, int l, int r, int L) {
        if (l == r) {
            return l;
        }

        int mid = (l + r) >> 1;

        if (tr[tr[p].lch].mn < L) {
            return query_mex(tr[p].lch, l, mid, L);
        } else {
            return query_mex(tr[p].rch, mid + 1, r, L);
        }
    }

    // a 下标从 1 开始，a.size() == n + 1
    void build(const vector<int>& a) {
        n = (int)a.size() - 1;

        tr.clear();
        tr.reserve((n + 1) * 20);

        root.assign(n + 1, 0);
        root[0] = build_empty(0, n);

        for (int i = 1; i <= n; i++) {
            root[i] = root[i - 1];

            // mex 最大只需要考虑 0 ~ n
            // 小于 0 或大于 n 的值不会影响 mex
            if (0 <= a[i] && a[i] <= n) {
                root[i] = update(root[i - 1], 0, n, a[i], i);
            }
        }
    }

    // 查询区间 [l, r] 的 mex
    // 要求 1 <= l <= r <= n
    int query(int l, int r) {
        return query_mex(root[r], 0, n, l);
    }
};