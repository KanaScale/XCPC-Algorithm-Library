// tarjan 求双连通分量
const int N = 2e5 + 10;
const int mod = 998244353;

vector<int> g[N], dcc[N];

int dfn[N], low[N], id;

int s[N], tp, p[N], cnt;

void tarjan(int u, int f = 0) {
	dfn[u] = low[u] = ++id, s[++tp] = u;
	for (int v : g[u]) {
		if (!dfn[v]) tarjan(v, u), low[u] = min(low[u], low[v]);
		else if (v != f) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		cnt++;
		for (int x = 0; x != u; ) {
			x = s[tp--], p[x] = cnt;
			dcc[cnt].emplace_back(x);
		}
	}
}