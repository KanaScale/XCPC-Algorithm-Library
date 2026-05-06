//必须外层枚举位，内层枚举集合s
vector<int> SOSDP(vector<int>& nums){
    int mx = bit_width((uint32_t)ranges::max(nums));
    vector<int> f(1 << mx);
    for (int x : nums) {
        f[x]++;
    }
    for (int i = 0; i < mx; i++) {
        for (int s = 0; s < (1 << mx); s++) {
            s |= 1 << i;
            f[s] += f[s ^ (1 << i)];
        }
    }
}