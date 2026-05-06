    const int B = sqrt(n);
    struct Block{
        int l,r;
        int todo;
    };
    vector<Block> blocks;
    for(int i = 0;i < n;i += B){
        int r = min(i + B,n);
        blocks.push_back({i,r,0});
    }
    auto add = [&](int l,int r,int v)->void{
        for(auto& b : blocks){
            if(b.r <= l) continue;
            if(b.l > r) break;
            if(l <= b.l && b.r <= r){
                b.todo += v;
            }else{
                for(int j = b.l;j < b.r;j++){
                    a[j] += b.todo;
                    if(j >= l && j <= r) a[j] += v;
                }
                b.todo = 0;
            }
        }
    };