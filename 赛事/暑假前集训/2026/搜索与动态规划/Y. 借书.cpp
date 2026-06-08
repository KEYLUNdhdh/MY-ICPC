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

void solve()
{
    int MAXW;
    cin >> MAXW;
    vector<i64> dp(MAXW + 1, 0);

    for (int sel = 1; sel <= 4;sel++)
    {
        int n;
        cin >> n;
        if(sel == 1)
        {
            for (int i = 0; i < n;i++)
            {
                i64 w, v, c;
                cin >> w >> v >> c;
                for (i64 k = 1; k <= c;k <<= 1)
                {
                    for (int j = MAXW; j >= k * w;j--)
                        chmax(dp[j], dp[j - k * w] + k * v);
                    c -= k;
                }
                if(c > 0)
                {
                    for (int j = MAXW; j >= c * w;j--)
                        chmax(dp[j], dp[j - c * w] + c * v);
                }
            }
        }
        else if(sel == 2)
        {
            for (int i = 0; i < n;i++)
            {
                i64 w, v;
                cin >> w >> v;
                for (int j = w; j <= MAXW;j++)
                    chmax(dp[j], dp[j - w] + v);
            }
        }
        else if(sel == 3)
        {
            vector<vector<int>> adj(n + 1);
            vector<vector<i64>> dpt(n + 1, vector<i64>(MAXW + 1, -1));
            vector<int> siz(n + 1, 0);
            vector<i64> val(n + 1, 0);
            vector<i64> w(n + 1, 0);
            for (int i = 1;i <= n;i++)
            {
                int p;
                cin >> w[i] >> val[i] >> p;
                adj[p].push_back(i);
            }

            auto dfs = [&](auto self, int u) -> void
            {
                siz[u] = w[u];
                dpt[u][w[u]] = val[u];
                for(int v : adj[u])
                {
                    self(self, v);

                    for (int j = min(MAXW, siz[u] + siz[v]); j >= w[u];j--)
                    {
                        if(dpt[u][j] == -1)
                            continue;
                        for (int k = min(siz[v], MAXW - j); k >= 0;k--)
                            if(dpt[v][k] != -1)
                                chmax(dpt[u][j + k], dpt[u][j] + dpt[v][k]);
                    }
                    siz[u] += siz[v];
                }
            };

            dfs(dfs, 0);
            vector<i64> nxt = dp;
            for (int j = 0; j <= MAXW;j++)
                for (int k = 0; k <= MAXW - j;k++)
                    if(dpt[0][k] != -1)
                        chmax(nxt[j + k], dp[j] + dpt[0][k]);

            dp = nxt;
        }
        else
        {
            map<int, vector<pll>> mp;
            for (int i = 0; i < n;i++)
            {
                int w, v, p;
                cin >> w >> v >> p;
                mp[p].push_back({w, v});
            }

            for(auto &[p, vec] : mp)
            {
                for (int j = MAXW; j >= 0;j--)
                {
                    for(auto &[w, v] : vec)
                    {
                        if(j >= w)
                            chmax(dp[j], dp[j - w] + v);
                    }
                }
            }
        }
    }
    i64 ans = 0;
    for (int i = 0; i <= MAXW;i++)
        chmax(ans, dp[i]);

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