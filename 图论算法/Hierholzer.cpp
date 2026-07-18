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


//欧拉通路的目标是走完所有边，每条边恰好走一次，并不要求经过所有点。

// 有向图欧拉通路 / 回路：
// 先忽略所有入度 = 出度 = 0 的孤立点。
// 所有有边相关的点，在无向意义下必须连通。

// 1. 欧拉回路：
//    所有点 indeg == outdeg
//    start 任选一个 outdeg > 0 的点。
//    如果没有边，start 随便选。

// 2. 欧拉通路但不是回路：
//    恰好一个点 outdeg == indeg + 1，start 必须选这个点。
//    恰好一个点 indeg == outdeg + 1，作为终点。
//    其他点 indeg == outdeg。

// 其他情况不存在欧拉通路。



// 无向图欧拉通路 / 回路：
// 先忽略所有度数为 0 的孤立点。
// 所有度数 > 0 的点必须在同一个连通块中。

// 1. 欧拉回路：
//    所有点度数为偶数
//    start 任选一个 degree > 0 的点。
//    如果没有边，start 随便选。

// 2. 欧拉通路但不是回路：
//    恰好两个点度数为奇数
//    start 选择这两个奇度点之一。

// 其他情况不存在欧拉通路。