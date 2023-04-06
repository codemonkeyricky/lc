

typedef long long ll;
constexpr int mod = 1e9 + 7;
constexpr int M = 10000;
int fact[M + 1];
int inv_fact[M + 1];

inline ll multiply(ll x, ll y)
{
    return x * y % mod;
}

inline ll binexp(ll x, int pow)
{
    if (pow == 0)
    {
        return 1;
    }
    ll half = binexp(x, pow >> 1);
    if (pow & 1)
    {
        return multiply(x, multiply(half, half));
    }
    return multiply(half, half);
}

inline ll comb(int m, int n)
{
    return multiply(fact[m], multiply(inv_fact[n], inv_fact[m - n]));
}

static const auto init = []
{
    fact[0] = 1;
    for (int i = 1; i <= M; ++i)
        fact[i] = multiply(fact[i - 1], i);

    inv_fact[M] = binexp(fact[M], mod - 2);
    for (int i = M - 1; i >= 0; --i)
        inv_fact[i] = multiply(i + 1, inv_fact[i + 1]);

    return false;
}();