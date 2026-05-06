class XorBasis {
    vector<int> b;

public:
    XorBasis(int n) : b(n) {}

    void insert(int x) {
        for (int i = b.size() - 1; i >= 0; i--) {
            if (x >> i) {
                if (b[i] == 0) {
                    b[i] = x;
                    return;
                }
                x ^= b[i];
            }
        }
    }

    int max_xor() {
        int res = 0;        
        for (int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
};