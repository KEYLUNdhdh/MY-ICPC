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
using u32 = unsigned int;
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

void solve()
{
    int n, l, k;
    cin >> n >> l >> k;

    vector<i64> d(n + 2, 0), a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> d[i];
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    d[n + 1] = l;

    vector<vector<i64>> dp(n + 2, vector<i64>(k + 1, INF));
    dp[1][0] = 0;
    for (int i = 1; i <= n + 1;i++)
    {
        for (int j = 0; j <= k;j++)
        {
            for (int p = 1; p < i;p++)
            {
                i64 lim = a[p];
                i64 dis = d[i] - d[p];
                int miss = i - p - 1;
                if(miss > j)
                    continue;
                chmin(dp[i][j], dp[p][j - miss] + lim * dis);
            }
        }
    }

    i64 ans = INF;
    for (int i = 0; i <= k;i++)
        chmin(ans, dp[n + 1][i]);

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