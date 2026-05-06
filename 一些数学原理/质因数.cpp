//因数个数
//[1,1e5] 中约数最多的数有 128 个，是 83160
//[1,1e6] 中约数最多的数有 240 个，是 720720
//[1,1e9] 中约数最多的数有 1344 个，是 735134400
//[1,1e12] 中约数最多的数有 6720 个，是 963761198400
//[1,1e18] 中约数最多的数有 103680 个，是 897612484786617600
//质数个数
//不超过1e5的质数共有 9592 个。



//一、埃氏筛
const int MX = 1'000'001;
bool is_prime[MX];
vector<int> primes;
auto init = []
{
    for (int i = 0; i < MX; i++)
        is_prime[i] = true;
    is_prime[0] = is_prime[1] = false; // 0 和 1 不是质数
    for (int i = 2; i < MX; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for (long long j = 1LL * i * i; j < MX; j += i)
            {
                is_prime[j] = false; // j 是质数 i 的倍数
            }
        }
    }
    return 0;
}();






//二、LPF
const int MX = 1'000'001;
int lpf[MX];
int init = [] {
    for (int i = 2; i < MX; i++) {
        if (lpf[i] == 0) { // i 是质数
            for (int j = i; j < MX; j += i) {
                if (lpf[j] == 0) { // 首次访问 j
                    lpf[j] = i;
                }
            }
        }
    }
    return 0;
}();

vector<pair<int,int>> prime_factorization(int x) {
    vector<pair<int,int>> res;
    while (x > 1) {
        int p = lpf[x];
        int e = 1;//（最小质因子的个数）
        for (x /= p; x % p == 0; x /= p) {
            e++;
        }
        res.emplace_back(p, e);
    }
    return res;
}






//三、因数分解 
const int N = 200005;
vector<int> divs[N];
int init = [] {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    return 0;
}();