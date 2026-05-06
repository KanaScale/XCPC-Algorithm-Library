mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r)
{
    return uniform_int_distribution<int>(l, r)(rng);
}
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// ll rng(ll l, ll r)
// {
//     return uniform_int_distribution<ll>(l, r)(rng);
// }