/*
lower_bound(begin, end, value, comp);
    comp(element, value)
    返回第一个不满足comp的位置

upper_bound(begin, end, value, comp);
    comp(value, element)
    返回第一个满足comp的位置
*/

/*
例：求给定区间覆盖到的区间数量
auto get = [&](int l,int r,vector<pii>& p)->int{
    int i = lower_bound(all(p),l,[](const pii& x,int val){
        return x.S < val;
    }) - p.begin();
    int j = upper_bound(all(p),r,[](int val,const pii& x){
        return x.F > val;
    }) - p.begin();
    return max(j - i,0);
};
*/