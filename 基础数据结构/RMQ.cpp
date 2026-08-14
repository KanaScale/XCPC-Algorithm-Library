class RMQ_max
{
    vector<vector<int>> st;
    int ope(const int &a, const int &b) { return max(a, b); };

public:
    RMQ_max(vector<int> &a)
    {
        build(a);
    }
    RMQ_max() {}
    void build(vector<int> &a)
    {
        int n = a.size();
        int m = __lg(n) + 1;
        st.resize(n);
        for (int i = 0; i < n; i++)
        {
            st[i].resize(m);
            st[i][0] = a[i];
        }
        for (int j = 1; j < m; j++)
        {
            for (int i = 0; i + (1 << j) <= n; i++)
            {
                st[i][j] = ope(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    //[l,r]
    int query(int l, int r)
    {
        r++;
        int k = __lg(r - l);
        return ope(st[l][k], st[r - (1 << k)][k]);
    }
};