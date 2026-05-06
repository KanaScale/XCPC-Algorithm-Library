int LPS(string s) {
    int n = s.length();
    if (n == 0) return 0;

    // 一维数组，代表二维算法中的 f[j]
    vector<int> f(n, 0);
    
    for (int i = n - 1; i >= 0; i--) {
        f[i] = 1;      // 相当于 f[i][i] = 1
        int prev = 0;   // prev 用来存储二维中的 f[i+1][j-1]
        
        for (int j = i + 1; j < n; j++) {
            int temp = f[j]; // 在 f[j] 被覆盖前，先保存下来，供下一个 j 当作 prev 使用
            
            if (s[i] == s[j]) {
                // f[i+1][j-1] + 2
                f[j] = prev + 2; 
            } else {
                // max(f[i+1][j], f[i][j-1])
                f[j] = max(f[j], f[j - 1]); 
            }
            
            prev = temp; // 滚动向前
        }
    }
    
    return f[n - 1];
}