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
mt19937 rnd(time(0));

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
    vector<int> ind(n + 1, 0), oud(n + 1, 0);
    vector<vector<int>> adj(n + 1);

    vector<int> cur(n + 1, 0);
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        oud[u]++;
        ind[v]++;
    }

    for (int i = 1; i <= n;i++)
    {
        if(ind[i] != oud[i] || (n > 1 && ind[i] == 0))
        {
            cout << -1;
            return;
        }
    }

    vector<int> ans;

    auto dfs = [&](auto self, int u) -> void
    {
        while(cur[u] < adj[u].size())
        {
            int v = adj[u][cur[u]++];
            self(self, v);
        }

        ans.push_back(u);
    };

    dfs(dfs, 1);

    if(ans.size() != m + 1)
    {
        cout << -1;
        return;
    }

    for (int i = ans.size() - 1; i >= 0;i--)
        cout << ans[i] << " ";
    
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