class WeightedDSU {
private:
    vector<int> parent;
    vector<long long> weight; // weight[x] = Value[x] - Value[parent[x]]
    int count;

public:
    explicit WeightedDSU(int n) {
        parent.resize(n);
        weight.resize(n, 0);
        count = n;
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            weight[i] = 0;
        }
    }
    int find(int x) {
        assert(x >= 0 && x < parent.size());
        if (x != parent[x]) {
            int root = find(parent[x]);
            weight[x] += weight[parent[x]];
            parent[x] = root;
        }
        return parent[x];
    }
    bool merge(int u, int v, long long w) {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u == root_v) {
            return false;
        }
        parent[root_v] = root_u;
        weight[root_v] = w + weight[u] - weight[v];
        count--; 
        return true;
    }
    bool is_connected(int u, int v) {
        return find(u) == find(v);
    }
    long long get_diff(int u, int v) {
        assert(is_connected(u, v));
        // (Value[v] - Value[Root]) - (Value[u] - Value[Root]) = Value[v] - Value[u]
        return weight[v] - weight[u];
    }
    int get_count() const {
        return count;
    }
};