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
    i64 n, k;
    cin >> n >> k;
    vector<i64> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i] >> b[i];

    vector<vector<array<i64, 2>>> dp(n + 1, vector<array<i64, 2>>(k + 1, {-INF, -INF}));
    dp[0][0][0] = 0;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 0; j <= k;j++)
        {
            if(j >= 1)
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0]) + b[i];
        
            dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1]) + a[i];
        }
    }   

    i64 maxx = 0;
    for (int i = 0; i <= k;i++)
        maxx = max({maxx, dp[n][i][0], dp[n][i][1]});

    cout << maxx;
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