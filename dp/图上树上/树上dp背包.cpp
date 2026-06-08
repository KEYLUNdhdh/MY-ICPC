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
// P_2014_CTSC_1997_选课
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> s(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        int k;
        cin >> k >> s[i];
        adj[k].push_back(i);
    }

    vector<vector<i64>> dp(n + 1, vector<i64>(m + 2, 0));
    vector<i64> siz(n + 1, 0);
    auto dfs = [&](auto self, int u) -> void //本质分组背包
    {
        siz[u] = 1;
        dp[u][1] = s[u];

        for(int v : adj[u])//每一组，也就是每一个儿子
        {
            self(self, v);

            for (int j = min<i64>(m + 1, siz[u] + siz[v]); j >= 1;j--)//循环背包容量。
            {

                for (int k = 0; k <= min<i64>(siz[v], j - 1);k++)//循环每个物品。
                    chmax(dp[u][j], dp[u][j - k] + dp[v][k]);
            }
            siz[u] += siz[v];
        }
    };

    dfs(dfs, 0);
    cout << dp[0][m + 1];
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