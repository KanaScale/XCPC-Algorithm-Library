const int MOD = 1'000'000'007;
const int N = 100'000;

long long F[N]; // F[i] = i!
long long INV_F[N]; // INV_F[i] = i!^-1

long long qpow(long long x, int n) {
    long long res = 1;
    for (; n; n /= 2) {
        if (n % 2) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

auto init = [] {
    F[0] = 1;
    for (int i = 1; i < N; i++) {
        F[i] = F[i - 1] * i % MOD;
    }

    INV_F[N - 1] = qpow(F[N - 1], MOD - 2);
    for (int i = N - 1; i; i--) {
        INV_F[i - 1] = INV_F[i] * i % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    return F[n] * INV_F[m] % MOD * INV_F[n - m] % MOD;
}

//n很大，O(m)
long long comb2(long long n,int m){
    n = n % MOD;
    long long res = 1;
    for (int i = 0; i < m; i++) {
        res = res * (n - i + MOD) % MOD;
    }
    res = res * INV_F[m] % MOD;
    return res;
}