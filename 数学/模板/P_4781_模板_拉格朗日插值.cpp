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
constexpr i64 MOD = 998244353, INF = 1e9;

template<class T>
T qpow(T a,T b,T MOD)
{
    T res = 1;
    a = (a % MOD + MOD) % MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}

template <class T>
T inv(T a,T p)
{
    return qpow(a, p - 2, p);
}

struct Lagrange
{
    int n;
    vector<i64> x, y;

    Lagrange() : n(0) {}

    void addPoint(i64 px, i64 py)
    {
        x.push_back(px);
        y.push_back(py);
        n++;
    }

    i64 query(i64 k)
    {
        k = (k % MOD + MOD) % MOD;
        i64 ans = 0;
        for (int i = 0;i < n;i++)
        {
            i64 num = 1;
            i64 den = 1;

            for (int j = 0;j < n;j++)
            {
                if(i == j)
                    continue;

                num = num * (k - x[j] + MOD) % MOD;
                den = den * (x[i] - x[j] + MOD) % MOD;
            }

            i64 term = y[i] * num % MOD * inv(den, MOD) % MOD;
            ans = (ans + term) % MOD;
        }
        return ans;
    }
};
void solve()
{
    int n, k;
    cin >> n >> k;
    Lagrange lg;

    for (int i = 0; i < n;i++)
    {
        i64 x, y;
        cin >> x >> y;
        lg.addPoint(x, y);
    }

    cout << lg.query(k);
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