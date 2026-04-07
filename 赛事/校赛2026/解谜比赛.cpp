#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<i64, i64> pii;

struct po
{
    i64 id, t, type;//1  0
    bool operator>(const po& b) const
    {
        return t > b.t;
    }
};
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    vector<i64> ans(n + 1, -1);
    priority_queue<po, vector<po>, greater<po>> pq;
    for (int i = 1; i <= k;i++)
    {
        int t, sc;
        cin >> t >> sc;
        for (int i = 0; i < sc;i++)
        {
            int u;
            cin >> u;
            pq.push({u, t, 1});
        }
    }
    for (int i = 1; i <= n;i++)
    {
        if(a[i] == 0)
            pq.push({i, 0, 1});
    }
    vector<vector<pii>> adj(n + 1);
    vector<i64> en(n + 1, 0);
    for (int i = 0; i < m;i++)
    {
        i64 u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    while(!pq.empty())
    {
        auto [u, t, type] = pq.top();
        pq.pop();
        if(ans[u] != -1)
            continue;
        int f = 0;//f 解锁
        if(type)
            f = 1;
        else
        {
            en[u]++;//energy
            if(en[u] >= a[u])
                f = 1;
        }
        if(f)
        {
            ans[u] = t;
            for(auto &[v, w] : adj[u])
                pq.push({v, t + w, 0});
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