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

i64 qpow(i64 a, i64 b, i64 p)
{
    i64 res = 1;
    a %= p;
    while(b)
    {
        if(b & 1)
            res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }

    cout << res % p;
    return res;
}

i64 inv(i64 a, i64 p)
{
    return qpow(a, p - 2, p);
}

void solve()
{
    i64 n, k, p;
    cin >> n >> k >> p;

    i64 up = n * (3 * n + 1) / 2;
    vector<vector<i64>> dp(n + 1, vector<i64>(up + 1, 0));
    vector<vector<i64>> nxt(n + 1, vector<i64>(up + 1, 0));
    dp[0][0] = 1;

    int ca, cu = 0;
    for (int i = 1;i <= 2 * n;i++)
    {
        nxt.assign(n + 1, vector<i64>(up + 1, 0));
        for (int cu = 0; cu <= n;cu++)
        {
            int ca = i - 1 - cu;
            if(ca < 0 || ca > n)
                continue;

            for (int suma = 0; suma <= up;suma++)
            {
                if(dp[cu][suma] == 0)
                    continue;
                if(ca < n && suma + i <= up)
                    nxt[cu][suma + i] = (nxt[cu][suma + i] + dp[cu][suma]) % p;

                if(cu < n)
                {
                    i64 m = min<i64>(n - cu, ca - cu + 1);
                    if(m > 0)
                        nxt[cu + 1][suma] = (nxt[cu + 1][suma] + dp[cu][suma] * m) % p;
                }
            }
        }

        swap(dp, nxt);
    }

    i64 ans = 0;
    for (int i = k; i <= up;i++)
        ans = (ans + dp[n][i]) % p;

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