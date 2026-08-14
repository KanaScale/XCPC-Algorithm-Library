//错排数 Dn 表示：
//n 个元素排列后，没有任何元素留在原位置的排列数量。
// Dn = n! * Σ(-1)^k / k!，k∈[0,n]
const int MOD = 998244353;
const int N = 1000005;

long long der[N];

void init_derangement()
{
    der[0] = 1;
    der[1] = 0;

    for(int i = 2; i < N; i++){
        der[i] = 1LL * (i - 1) * (der[i - 1] + der[i - 2]) % MOD;
    }
}