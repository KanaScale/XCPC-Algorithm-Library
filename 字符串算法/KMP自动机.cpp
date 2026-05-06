//aut[i][c]。它表示：当前已经匹配了 S 的前 i 个字符，如果接下来读取到字符 c，匹配长度会变成多少
vector<vector<int>> aut(m, vector<int>(26, 0));
aut[0][S[0] - 'a'] = 1;
int x = 0; // x 表示当前状态的最长 proper prefix 也就是失配指针 (fail)
for (int i = 1; i < m; ++i) {
    for (int c = 0; c < 26; ++c) {
        if (S[i] - 'a' == c) {
            aut[i][c] = i + 1;
        } else {
            aut[i][c] = aut[x][c];
        }
    }
    x = aut[x][S[i] - 'a']; // 更新边界失配指针
}
int pi_m = x; // 当匹配满长度 m 后，下一个状态要回退到的节点