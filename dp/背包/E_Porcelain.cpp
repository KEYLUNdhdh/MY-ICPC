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
    int n, m;
    cin >> n >> m;

    vector<vector<i64>> a(n + 1);
    vector<int> num(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> num[i];
        a[i].assign(num[i] + 1, 0);
        for (int j = 1; j <= num[i];j++)
            cin >> a[i][j];
    }

    vector<vector<i64>> best(n + 1);
    vector<i64> dp(m + 1, 0);

    vector<i64> pre, suf;
    for (int i = 1; i <= n;i++)
    {
        best[i].assign(num[i] + 1, 0);
        pre.assign(num[i] + 1, 0);
        suf.assign(num[i] + 2, 0);
        for (int j = 1;j <= num[i];j++)
            pre[j] = pre[j - 1] + a[i][j];

        for (int j = num[i]; j >= 1;j--)
            suf[j] = suf[j + 1] + a[i][j];

        for (int x = 1; x <= m && x <= num[i];x++)
        {
            i64 maxx = 0;
            for (int k = 0; k <= x;k++)
                chmax(best[i][x], pre[k] + suf[num[i] - (x - k) + 1]);
        }
    }

    for (int i = 1; i <= n;i++)
    {
        for (int w = m; w >= 0;w--)
        {
            for (int c = 0; c <= num[i] && c <= m && c <= w;c++)
                chmax(dp[w],dp[w - c] + best[i][c]);
        }
    }

    // for (int i = 1;i <= n;i++)
    // {
    //     for (int j = 0; j <= num[i];j++)
    //         cerr << best[i][j] << " ";

    //     cerr << "\n";
    // }
        cout << dp[m];
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