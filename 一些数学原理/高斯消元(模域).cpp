const long long MOD = 1e9 + 7; // 根据题目要求修改模数

// 快速幂求逆元 (前提: MOD 必须是质数)
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long inv(long long n) {
    return power(n, MOD - 2);
}

/**
 * 高斯-约旦消元法 (模 MOD 意义下)
 * @param a 增广矩阵，大小为 n * (m + 1)，n 个方程，m 个未知数
 * @param ans 用于存放解的数组
 * @return 1 表示有唯一解, 0 表示无解, -1 表示有无穷多解
 */
int gauss_jordan(vector<vector<long long>>& a, vector<long long>& ans) {
    int n = a.size();           // 方程个数 (行数)
    if (n == 0) return -1;
    int m = a[0].size() - 1;    // 未知数个数 (列数 - 1)
    
    int row = 0; // 当前处理到的有效方程行数
    
    // 遍历每一列 (未知数)
    for (int col = 0; col < m && row < n; ++col) {
        // 1. 寻找当前列的非零主元 (Pivot)
        int pivot = row;
        for (int i = row; i < n; ++i) {
            if (a[i][col] != 0) {
                pivot = i;
                break;
            }
        }
        
        // 如果当前列全为 0，说明这个未知数是自由变量，跳过，处理下一列
        if (a[pivot][col] == 0) continue; 
        
        // 2. 将找到的非零主元行交换到当前行
        swap(a[row], a[pivot]);
        
        // 3. 将主元系数化为 1 (乘以逆元)
        long long inv_val = inv(a[row][col]);
        for (int j = col; j <= m; ++j) {
            a[row][j] = (a[row][j] * inv_val) % MOD;
        }
        
        // 4. 用主元行去消掉其他所有行的当前列 (高斯-约旦的精髓：上下都消)
        for (int i = 0; i < n; ++i) {
            if (i != row && a[i][col] != 0) {
                long long factor = a[i][col];
                for (int j = col; j <= m; ++j) {
                    a[i][j] = (a[i][j] - factor * a[row][j]) % MOD;
                    if (a[i][j] < 0) a[i][j] += MOD; // 保持正数
                }
            }
        }
        
        row++; // 该行已经被完美处理，处理下一行
    }
    
    // ================= 解的判定 =================
    
    ans.assign(m, 0);
    
    // 判断是否有产生 0 = 非零 的矛盾方程 (无解)
    for (int i = row; i < n; ++i) {
        if (a[i][m] != 0) return 0; // 无解
    }
    
    // 有效方程数小于未知数个数，说明存在自由变量 (无穷多解)
    if (row < m) return -1; 
    
    // 提取唯一解
    for (int i = 0; i < m; ++i) {
        ans[i] = a[i][m];
    }
    
    return 1; // 唯一解
}