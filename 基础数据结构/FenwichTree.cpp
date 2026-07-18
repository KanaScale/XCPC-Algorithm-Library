class FenwichTree
{
    vector<int> t;
    int hb;

public:
    FenwichTree(int n) : t(n + 1), hb(1 << __lg(n)) {}
    void update(int i, int val)
    {
        for (i += 1; i < t.size(); i += i & -i)
        {
            t[i] += val;
        }
    }
    long long pre(int i)
    {
        long long res = 0;
        for (i += 1; i > 0; i -= i & -i)
        {
            res += t[i];
        }
        return res;
    }
    long long query(int l, int r)
    {
        if (r < l)
            return 0;
        return pre(r) - pre(l - 1);
    }
    int kth(int k)
    {
        int res = 0;
        for (int b = hb; b > 0; b >>= 1)
        {
            int nxt = res | b;
            if (nxt < t.size() && k > t[nxt])
            {
                k -= t[nxt];
                res = nxt;
            }
        }
		//注意这里是值域树状数组，值-频数
        return res + 1 < t.size() ? res : -1;
    }
};