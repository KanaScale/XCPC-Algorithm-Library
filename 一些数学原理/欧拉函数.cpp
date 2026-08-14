// φ(x) = #{1 <= k <= x : gcd(k,x) = 1}
// #{x : gcd(x,n) = d} = φ(n/d)


//一、直接求 O(N ^ 0.5)
long long phi(long long n)
{
    long long res = n;

    for(long long p = 2; p * p <= n; p++){
        if(n % p == 0){
            res = res / p * (p - 1);

            while(n % p == 0)
                n /= p;
        }
    }

    if(n > 1)
        res = res / n * (n - 1);

    return res;
}




//二、批量求 1∼N 的欧拉函数：线性筛 O(N)
const int N = 1000005;

int phi[N];
vector<int> primes;
bool vis[N];

void init_phi()
{
    phi[1] = 1;

    for(int i = 2; i < N; i++){
        if(!vis[i]){
            primes.push_back(i);
            phi[i] = i - 1;
        }

        for(int p : primes){
            if(1LL * i * p >= N)
                break;

            vis[i * p] = true;

            if(i % p == 0){
                phi[i * p] = phi[i] * p;
                break;
            }else{
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}




//三、易知质因数分解
long long phi(int n)
{
    auto fac = prime_factorization(n);

    long long res = n;

    for(auto [p, e] : fac)
        res = res / p * (p - 1);

    return res;
}