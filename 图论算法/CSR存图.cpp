//CSR（Compressed Sparse Row，压缩稀疏行）扁平化存图
//不支持动态加边，必须加入所有边后work()编译
//图类型(1有向图,2无向图)、边权类型
//E.init(n); //初始化
//E.addEdge(u,v,w); //加边
//E.work(); //编译
//for(auto [v, w] : G[u]) //遍历
template<int D, typename WT> struct GraphW{
    vector<pair<int, WT>> E; vector<int> LOC; 
    vector<tuple<int,int,WT>> T;
    int *I, *II;  
    void init(int n, int m){
        init(n); T.reserve(m); 
        for(int i = 0; i < m; ++i){
            int u = rd() - 1, v = rd() - 1;
            addEdge(u, v, rd()); //
        } work();
    }
    void init(int n){
        LOC.assign(n+2, 0); T.clear(); 
        I = LOC.data()+1; II = LOC.data()+2;
    }
    void addEdge(int u, int v, WT w){
        T.emplace_back(u,v,w);
        ++II[u]; if constexpr(D == 2) ++II[v];
    }
    void work(){
        for(int i = 0; i < LOC.size() - 2; ++i) II[i] += II[i-1];
        E.reserve(LOC.back()); 
        for(auto EP = E.data(); auto &[u,v,w] : T){
            EP[I[u]++] = {v,w}; if constexpr(D == 2) EP[I[v]++] = {u,w};
        }
    }
    struct RG{
        pair<int,WT> *Begin , *End;
        RG(pair<int,WT> *a,pair<int,WT> *b):Begin(a),End(b){}
        auto &begin(){return Begin;}
        auto &end(){return End;}
        auto size(){return End - Begin;}
        auto operator[](int i){return Begin[i];}
    };  
    auto operator[](int i){
        return RG(E.data() + LOC[i], E.data() + LOC[i+1]);
    } 
}; 