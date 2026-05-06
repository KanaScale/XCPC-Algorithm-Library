// tarjan 求双连通分量
const int MAXN = 2e5 + 10;
const int mod = 998244353;

vector<int> g[MAXN], dcc[MAXN];

int dfn[MAXN], low[MAXN], id;

int s[MAXN], tp, p[MAXN], cnt;

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