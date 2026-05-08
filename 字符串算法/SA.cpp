class SuffixArray {
private:
    int n;
    string s;
    vector<int> sa; // sa[i]: 排名为 i 的后缀在原串中的起始位置
    vector<int> rk; // rk[i]: 以位置 i 起始的后缀的排名
    vector<int> ht; // ht[i]: 排名为 i 和 i-1 的后缀的最长公共前缀 (LCP) 长度

public:
    SuffixArray() : n(0) {}
    
    SuffixArray(const string& str) : s(str), n(str.length()) {
        sa.resize(n);
        rk.resize(n);
        ht.resize(n);
        if (n == 0) return;

        vector<int> y(n), c(n);
        int m = 256; // 字符集大小 (ASCII)

        // 第一轮：按单个字符进行基数排序
        vector<int> cnt(max(m, n), 0);
        for (int i = 0; i < n; ++i) ++cnt[rk[i] = (unsigned char)s[i]];
        for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) sa[--cnt[rk[i]]] = i;

        // 倍增过程
        for (int w = 1; w < n; w <<= 1) {
            int p = 0;
            // y 数组存的是按照第二关键字排序后的后缀起始位置
            for (int i = n - w; i < n; ++i) y[p++] = i;
            for (int i = 0; i < n; ++i) {
                if (sa[i] >= w) y[p++] = sa[i] - w;
            }

            // 对第一关键字进行基数排序
            fill(cnt.begin(), cnt.begin() + m, 0);
            for (int i = 0; i < n; ++i) ++cnt[rk[y[i]]];
            for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) sa[--cnt[rk[y[i]]]] = y[i];

            swap(rk, y);
            rk[sa[0]] = 0;
            p = 1;
            // 重新计算离散化后的排名
            for (int i = 1; i < n; ++i) {
                rk[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && 
                             (sa[i] + w < n ? y[sa[i] + w] : -1) == 
                             (sa[i - 1] + w < n ? y[sa[i - 1] + w] : -1)) ? p - 1 : p++;
            }
            if (p == n) break; // 所有的排名都已经不同，提前结束
            m = p;             // 下一次基数排序的最大值域
        }

        // 构建 Height 数组 (LCP: Longest Common Prefix)
        // ht[i] = LCP(suffix(sa[i-1]), suffix(sa[i]))
        for (int i = 0, k = 0; i < n; ++i) {
            if (rk[i] == 0) continue; // 排名第一的后缀没有前一个后缀
            if (k) --k;               // 利用 h[i] >= h[i-1] - 1 的性质
            int j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            ht[rk[i]] = k;
        }
    }
 
    // 计算并返回字符串中本质不同的子串数量
    long long distinct_substrings_count() const {
        if (n == 0) return 0;
        // 注意：总子串数可能超出 32 位整数范围，必须使用 long long 避免溢出
        long long ans = 1LL * n * (n + 1) / 2;
        // ht[0] 恒为 0，有效计算从 1 开始
        for (int i = 1; i < n; ++i) {
            ans -= ht[i];
        }
        return ans;
    }

    // 提供对外的单点访问接口
    int get_sa(int i) const { return sa[i]; }
    int get_rk(int i) const { return rk[i]; }
    int get_ht(int i) const { return ht[i]; }
    
    // 提供完整的数组常数引用获取
    const vector<int>& get_sa_array() const { return sa; }
    const vector<int>& get_rk_array() const { return rk; }
    const vector<int>& get_ht_array() const { return ht; }
    
    int size() const { return n; }
};

/* 
// 用给定的字符串初始化后缀数组，自动计算 sa, rk 和 ht 数组。时间复杂度 O(N log N)
SuffixArray(const string& str);
 
// 获取原字符串中“本质不同”的子串数量。 
long long get_distinct_substrings_count() const;
  
// 获取字典序排名为 i 的后缀在原字符串中的起始下标。
// 参数: i (0 <= i < n)
int get_sa(int i) const;

// 获取原字符串中以索引 i 开头的后缀的字典序排名。
// 参数: i (0 <= i < n)
int get_rk(int i) const;

// 获取字典序排名为 i 的后缀与其前一名的后缀 (排名为 i-1) 的最长公共前缀 (LCP) 长度。
// 注意: get_ht(0) 恒等于 0，因为排名第 0 的后缀没有前一个后缀。
// 参数: i (0 <= i < n)
int get_ht(int i) const; 

// 获取内部处理的字符串长度
int size() const; 
*/