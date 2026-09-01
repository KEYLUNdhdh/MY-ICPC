#include <bits/stdc++.h>
#define lyc_fan_club main
#ifndef ONLINE_JUDGE
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x) {       \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(x)
#define debugarr(x)
#define cutline
#endif
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
bool ST;

constexpr i64 MOD = 998244353, INF = 2e18;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pll>> adj(n + 1);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    vector<i64> dist(n + 1, INF);
    pq.push({0, n});
    while(!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if(d >= dist[u])
            continue;
        dist[u] = d;
        for(auto &[w, v] : adj[u])
        {
            if(dist[u] + w < dist[v])
                pq.push({dist[u] + w, v});
        }
    }
    debug(n)

    if(dist[1] == INF)
    {
        cout << "inf";
        return;
    }
    debug(n)
    vector<i64> d;
    for (int i = 1; i <= n;i++)
        d.push_back(min(dist[i], dist[1]));

    sort(d.begin(), d.end());
    d.erase(unique(d.begin(), d.end()), d.end());
    reverse(d.begin(), d.end());
    debug(n)

    vector<pair<string, i64>> ans;
    debugarr(d)
    for (int i = 0; i < d.size() - 1;i++)
    {
        i64 cur = d[i];
        i64 nx = d[i + 1];
        i64 t = cur - nx;
        debug(t)
        string s = "";
        for (int j = 1; j <= n;j++)
        {
            if(dist[j] >= cur)
                s += '1';
            else
                s += '0';
        }
        ans.push_back({s, t});
    }
    debug(n)
    cout << dist[1] << " " << ans.size() << "\n";
    for (auto &[s, t] : ans)
        cout << s << " " << t << "\n";
    return;
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}