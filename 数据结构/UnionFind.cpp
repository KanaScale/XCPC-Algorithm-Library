class UnionFind {
    vector<int> fa;
    vector<int> sz; 

public:
    int cc; 
    UnionFind(int n) : fa(n), sz(n, 1), cc(n) {
        iota(fa.begin(),fa.end(),0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    bool is_same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x == y) { 
            return false;
        }
        fa[x] = y; 
        sz[y] += sz[x]; 
        cc--;
        return true;
    }

    int get_size(int x) {
        return sz[find(x)]; 
    }
};