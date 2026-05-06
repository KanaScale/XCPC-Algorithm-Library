// 必败态（终止状态）的 SG 值为 0。
// 任意状态的 SG 值，等于它所有能一步到达的后继状态的 SG 值集合中，未出现过的最小非负整数（即 MEX 操作）。
// 如果有多个独立的子游戏同时进行（比如有多堆石头），总局面的 SG 值等于所有子游戏 SG 值的异或和。总 SG>0 则先手必胜。
const int MXS = 10005; // 状态的最大值
int sg[MXS];           // 记忆化数组

// 获取集合中未出现的最小非负整数 (Minimum Excluded)
int get_mex(const unordered_set<int>& S) {
    for (int i = 0; ; ++i) {
        if (S.find(i) == S.end()) {
            return i;
        }
    }
}

// 核心：计算某个状态 x 的 SG 值
int get_sg(int x) {
    // 1. 终止状态 (必败态)
    if (x == 0) return 0; // 假设 0 是不能再操作的状态
    
    // 2. 记忆化读取
    if (sg[x] != -1) return sg[x];
    
    unordered_set<int> next_states_sg;
    
    // 3. 遍历当前状态 x 能走到的所有下一步状态 y
    // 【这里的逻辑根据具体题目规则修改！】
    // 比如：每次只能拿 1个、3个 或 4个 石头
    vector<int> moves = {1, 3, 4}; 
    for (int step : moves) {
        if (x >= step) {
            int y = x - step; // 下一个状态
            next_states_sg.insert(get_sg(y));
        }
    }
    
    // 4. 当前状态的 SG 值就是后继集合的 MEX
    return sg[x] = get_mex(next_states_sg);
}
 