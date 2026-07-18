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



//tarjan 求强连通分量SCC
//注意in_stk，用回边更新low时，必须确保y在栈中，不属于已被确定的分量
	vi dfn(2 * n,-1),low(2 * n,-1),bel(2 * n,-1),in_stk(2 * n);
	int N = 0,clk = 0; 
	vi stk;
	auto tarjan = [&](auto&& tarjan,int x)->void{
		dfn[x] = low[x] = ++clk;
		stk.pb(x);
		in_stk[x] = 1;
		for(auto& [y,w] : g[x]){
			if(dfn[y] == -1){
				tarjan(tarjan,y);
				low[x] = min(low[x],low[y]);
			}else if(in_stk[y]){
				low[x] = min(low[x],dfn[y]);
			}
		}
		if(dfn[x] == low[x]){ 
			while(stk.size()){
				int y = stk.back();stk.ob(); 
				bel[y] = N;
				in_stk[y] = 0;
				if(y == x) break;
			}
			N++; 
		}
	};
	fo(x,0,2 * n)if(dfn[x] == -1) tarjan(tarjan,x);