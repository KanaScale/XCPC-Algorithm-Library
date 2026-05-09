class BIT
{
    vector<ll> t;

public:
    BIT(int n) : t(n + 1, LLONG_MIN) {}
    void update(int i, ll v)
    {
        for (i += 1; i < t.size(); i += i & -i)
        {
            t[i] = max(t[i], v);
        }
    }
    ll pre_max(int i)
    {
        ll res = LLONG_MIN;
        for (i += 1; i > 0; i &= i - 1)
        {
            res = max(res, t[i]);
        }
        return res;
    }
};