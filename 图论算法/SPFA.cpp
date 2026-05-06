// SPFA 算法求解最短路与负权环检测
bool spfa(int n, const vector<vector<pair<int, int>>>& adj, vector<int>& dist) {
    queue<int> q;
    vector<bool> in_queue(n + 1, true);
    vector<int> cnt(n + 1, 0); // 记录到达某个点的最短路所经过的边数

    // 初始时将所有未知数节点入队，距离设为 0。
    // 这相当于建立了一个超级源点向所有节点连了一条权值为 0 的边，保证图的连通性。
    for (int i = 1; i <= n; i++) {
        dist[i] = 0;
        q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        // 遍历所有从 u 出发的边 (u -> v, 权重为 w)
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            // 如果满足松弛条件 (即存在更严苛的约束 x_v <= x_u + w)
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1; // 经过的边数 + 1
                
                // 抽屉原理：如果最短路的边数 >= n，说明必定绕了圈，存在负权环
                if (cnt[v] >= n) {
                    return false; // 存在逻辑矛盾，无解
                }

                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return true; // 成功求出合法解
}