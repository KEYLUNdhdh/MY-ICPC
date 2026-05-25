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
typedef tuple<int, int, int> piii;
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
    int n;
    cin >> n;
    vector<i64> r(n + 1, 0);

    for (int i = 1;i <= n;i++)
        cin >> r[i];

    vector<vector<int>> adj(n + 1);
    vector<int> ind(n + 1, 0);
    for (int i = 1; i < n;i++)
    {
        int l, k;
        cin >> l >> k;
        adj[k].push_back(l);
        ind[l]++;
    }

    int s = -1;
    for (int i = 1; i <= n;i++)
    {
        if(ind[i] == 0)
        {
            s = i;
            break;
        }
    }

    vector<array<i64, 2>> dp(n + 1, {0, 0});
    auto dfs = [&](auto self, int u, int p) -> void
    {
        for(int v : adj[u])
            self(self, v, u);

        dp[u][0] = 0;
        dp[u][1] = r[u];
        for(int v : adj[u])
        {
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    };

    dfs(dfs, s, 0);
    cout << max(dp[s][1], dp[s][0]);
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