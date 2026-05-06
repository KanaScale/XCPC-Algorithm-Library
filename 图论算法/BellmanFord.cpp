vector<long long> dist(n + 1, INF);
dist[0] = 0;

// 使用纯正的 Bellman-Ford，无视任何刻意针对 SPFA 的卡时操作
// 一个简单图的最短路最多包含 n 条边，因此最多迭代 n 次
for (int step = 1; step <= n; ++step) {
    bool updated = false;
    for (const auto& edge : edges) {
        if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.w) {
            dist[edge.v] = dist[edge.u] + edge.w;
            updated = true;
        }
    }
    // 如果某一轮没有任何更新，说明最短路已经全部找完，提前结束
    if (!updated) break;
}

// 第 n + 1 次探测：如果还能更新，说明必然存在死循环的负权环
bool has_negative_cycle = false;
for (const auto& edge : edges) {
    if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.w) {
        has_negative_cycle = true;
        break;
    }
}