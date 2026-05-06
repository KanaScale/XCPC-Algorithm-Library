// 对于每个右端点 i，计算所有子数组的或值，打印这些或值的分布范围（子数组左端点范围）
// 时间复杂度 O(nlogU)，其中 U = max(nums)
void logTrick(vector<int>& nums) {
    vector<pair<int, int>> or_left; // (子数组或值，最小左端点)
    for (int i = 0; i < nums.size(); i++) {
        int x = nums[i];
        // 计算以 i 为右端点的子数组或值
        for (auto& [or_val, _] : or_left) {
            or_val |= x; // **根据题目修改**
            //常用：根据连续的包含于关系，利用子集性质剪枝
        }
        // x 单独一个数作为子数组
        or_left.emplace_back(x, i);

        // 原地去重（相同或值只保留最左边的）
        int m = 1;
        for (int j = 1; j < or_left.size(); j++) {
            if (or_left[j].first != or_left[j - 1].first) {
                or_left[m++] = or_left[j];
            }
        }
        or_left.resize(m);

        cout << i << " " << x << endl;
        for (int k = 0; k < m; k++) {
            auto [or_val, left] = or_left[k];
            int right = k + 1 < m ? or_left[k + 1].second - 1 : i;
            // 对于左端点在 [left, right]，右端点为 i 的子数组，OR 值都是 or_val
            cout << left << " " << right << " " << or_val << endl;
        }
    }
} 
