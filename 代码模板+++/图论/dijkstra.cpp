#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<i64, i64> pll;

constexpr i64 MOD = 998244353, INF = 2e18;

void solve()
{
    int n, m ,s;
    cin >> n >> m >> s;

    vector<vector<pll>> adj(n + 1);
    for (int i = 0; i < m;i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    vector<i64> ans(n + 1, INF);

    ans[s] = 0;
    pq.push({0, s});
    while(!pq.empty())
    {
        auto [dis, u] = pq.top();
        pq.pop();

        if(dis > ans[u])
            continue;

        for(auto &[w, v] : adj[u])
        {
            if(ans[u] + w < ans[v])
            {
                ans[v] = ans[u] + w;
                pq.push({ans[v], v});
            }
        }
    }

    for (int i = 1; i <= n;i++)
        cout << ans[i] << " ";

}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}