
//原字符串s，判定子串[l,r]是否为回文串
    string t = "^";
    for(char c : s){
        t += '#';
        t += c;
    }
    t += "#$";
    vector<int> R(t.size() - 2);
    R[1] = 1;
    int m = 0,r = 0,maxi = 0;
    for(int i = 2;i < R.size();i++){
        int hl = 1;
        if(i < r) hl = min(R[m * 2 - i],r - i);
        while(t[i - hl] == t[i + hl]){
            hl++;
            m = i;
            r = i + hl;
        }
        R[i] = hl;
        if(R[i] > R[maxi]) maxi = i;
    }
    auto check = [&](int i,int j)->bool{
        if(i > j) return false;
        int l = (i + 1) * 2,r = (j + 1) * 2,len = j - i + 1;
        int m = (l + r) / 2;
        return R[m] - 1 >= len;
    };