vector<int> col(n,-1);
bool check(int u, int f = 0) {
	if (col[u] != -1) return col[u] == f; 
	col[u] = f;
	for (int v : g[u]) if (!check(v, f ^ 1)) return 0;
	return 1;
}