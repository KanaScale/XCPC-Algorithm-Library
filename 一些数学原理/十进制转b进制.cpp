// 把十进制字符串 s 转成 b 进制
// 用小学学过的【竖式除法】计算，读者可以先用竖式除法算算 1234÷10，再对照下面的代码
vector<int> trans(string& s, int b) {
    for (char& c : s) {
        c -= '0';
    }
    vector<int> digits;
    while (!s.empty()) {
        string nxt_s; // 用竖式除法计算 s / b 得到的商（十进制）
        int rem = 0; // s % b
        for (char c : s) { //执行一次竖式除法
            rem = rem * 10 + c;
            int q = rem / b; // 商
            if (q || !nxt_s.empty()) { // 忽略前导零
                nxt_s.push_back(q);
            }
            rem = rem % b;
        }
        digits.push_back(rem);
        s = move(nxt_s);
    }
    ranges::reverse(digits);
    return digits;
}