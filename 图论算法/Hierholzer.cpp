vector<vector<int>> ans;//递归栈
// 深度优先搜索（Hierholzer 算法）求解欧拉通路
function<void(int)> dfs = [&](int u) {
    while (!edges[u].empty()) {
        int v = edges[u].back();
        edges[u].pop_back();
        dfs(v);
        ans.push_back({u, v});
    }
};
dfs(start);
reverse(ans.begin(), ans.end());