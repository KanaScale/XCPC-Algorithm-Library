	vector pre(n + 1,vector<int>(m + 1));
    fo(i,0,n){
        fo(j,0,m){
            pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + (g[i][j] == 'g');
        }
    }
    auto query = [&](int x1,int y1,int x2,int y2)->int{
        x1 = max(0,x1);
        y1 = max(0,y1);
        x2 = min(n - 1,x2);
        y2 = min(m - 1,y2);
        return pre[x2 + 1][y2 + 1] - pre[x1][y2 + 1] - pre[x2 + 1][y1] + pre[x1][y1];
    };