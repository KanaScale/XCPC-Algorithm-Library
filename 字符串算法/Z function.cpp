//对于字符串 s，定义 z[i] 表示后缀 s[i:] 与 s 的 LCP（最长公共前缀）的长度，其中 s[i:] 表示从 s[i] 到 s[n−1] 的子串。
//常用技巧是构造字符串 pattern+s，如果发现 z[m+i]≥m（m 是 pattern 的长度），则说明从 s[i] 开始的子串与 pattern 匹配。
vector<int> calc_z(const string &s)
{
    int n = s.size();
    vector<int> z(n);
    z[0] = n; 
    int l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        //复用区间
        if (i <= r)
            z[i] = min(z[i - l], r - i + 1);
        //暴力匹配
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}