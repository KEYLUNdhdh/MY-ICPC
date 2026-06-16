#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr i64 MOD = 1004535809, INF = 1e9;
const int G = 3;

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

namespace NTT
{
    vector<i64> rev;
    void initRev(int limit)
    {
        if(rev.size() == limit)
            return;
        int l = __builtin_ctz(limit);
        rev.resize(limit);
        for (int i = 0; i < limit;i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    }

    void transform(vector<i64> &a, int flag)
    {
        int n = a.size();

        initRev(n);
        for(int i = 0;i < n;i++)
            if(i < rev[i])
                swap(a[i], a[rev[i]]);

        for (int mid = 1; mid < n;mid <<= 1)
        {
            i64 wn = qpow(G, (MOD - 1) / (mid << 1));
            if(flag == -1)
                wn = qpow(wn, MOD - 2);

            for (int i = 0; i < n;i += (mid << 1))
            {
                i64 w = 1;
                for (int j = 0; j < mid;j++, w = w * wn % MOD)
                {
                    i64 x = a[i + j];
                    i64 y = w * a[i + j + mid] % MOD;
                    a[i + j] = (x + y >= MOD ? x + y - MOD : x + y);
                    a[i + j + mid] = (x - y < 0 ? x - y + MOD : x - y);
                }
            }
        }

        if(flag == -1)
        {
            i64 invN = qpow(n, MOD - 2);
            for (int i = 0; i < n;i++)
                a[i] = a[i] * invN % MOD;
        }
    }
}

struct Poly
{
    vector<i64> a;

    Poly() {}
    Poly(int size) : a(size, 0) {}
    Poly(const vector<i64> &a_) : a(a_) {}
    Poly(initializer_list<i64> a_) : a(a_) {}

    int size() const { return a.size(); }
    void resize(int n) { a.resize(n); }

    i64 operator[](int idx) const { return idx < size() ? a[idx] : 0; }
    i64 &operator[](int idx) { return a[idx]; }

    Poly modXk(int k) const
    {
        k = min(k, size());
        return Poly(vector<i64>(a.begin(), a.begin() + k));
    }

    Poly mulXk(int k) const
    {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }

    friend Poly operator+(const Poly &A, const Poly &B)
    {
        Poly res(max(A.size(), B.size()));
        for (int i = 0; i < res.size(); i++)
            res[i] = (A[i] + B[i]) % MOD;
        return res;
    }

    friend Poly operator-(const Poly &A, const Poly &B)
    {
        Poly res(max(A.size(), B.size()));
        for (int i = 0; i < res.size(); i++)
            res[i] = (A[i] - B[i] + MOD) % MOD;
        return res;
    }
    
    friend Poly operator*(Poly A, Poly B)
    {
        if(A.size() == 0 || B.size() == 0)
            return Poly();

        int n = A.size(), m = B.size();
        int limit = 1;
        while(limit < n + m - 1)
            limit <<= 1;

        A.resize(limit);
        B.resize(limit);
        NTT::transform(A.a, 1);
        NTT::transform(B.a, 1);
        for (int i = 0; i < limit;i++)
            A[i] = A[i] * B[i] % MOD;

        NTT::transform(A.a, -1);
        A.resize(n + m - 1);
        return A;
    }

    friend Poly operator*(Poly A, i64 k)
    {
        k = (k % MOD + MOD) % MOD;
        for (int i = 0; i < A.size();i++)
            A[i] = A[i] * k % MOD;
        return A;
    }

    Poly deriv() const
    {
        if(size() <= 1)
            return Poly({0});
        Poly res(size() - 1);
        for (int i = 1;i < size(); i++)
            res[i - 1] = a[i] * i % MOD;
        return res;
    }

    Poly integr() const
    {
        Poly res(size() + 1);
        for (int i = 0; i < size();i++)
            res[i + 1] = a[i] * qpow(i + 1, MOD - 2) % MOD;
        return res;
    }

    Poly inv(int deg) const 
    {
        Poly res({qpow(a[0], MOD - 2)});
        int k = 1;
        while(k < deg)
        {
            k <<= 1;
            Poly cur = modXk(k);
            res = (res * (Poly({2}) - cur * res)).modXk(k);
        }
        return res.modXk(deg);
    }

    Poly ln(int deg) const
    {
        return (deriv() * inv(deg)).integr().modXk(deg);
    }

    Poly exp(int deg) const 
    {
        Poly res({1});
        int k = 1;
        while(k < deg)
        {
            k <<= 1;
            Poly cur = modXk(k);
            res = (res * (Poly({1}) - res.ln(k) + cur)).modXk(k);
        }
        return res.modXk(deg);
    }
};

void solve()
{
    i64 n;
    cin >> n;

    vector<i64> fac(n + 1, 1), invfac(n + 1, 1);
    for (int i = 1; i <= n;i++)
        fac[i] = fac[i - 1] * i % MOD;

    invfac[n] = qpow(fac[n], MOD - 2);
    for (int i = n - 1; i >= 0;i--)
        invfac[i] = invfac[i + 1] * (i + 1) % MOD;
    Poly g(n + 1);
    for (int i = 0; i <= n;i++)
    {
        i64 pow = 1ll * i * (i - 1) / 2 % (MOD - 1);
        i64 up = qpow(2, pow);
        g[i] = up * invfac[i] % MOD;
    }

    Poly f = g.ln(n + 1);
    i64 ans = f[n] * fac[n] % MOD;

    cout << ans;
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}