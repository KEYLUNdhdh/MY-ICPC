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
struct HLD 
{
    int n, root;
    vector<vector<int>> adj;
    vector<int> sz, dep, fa, son, top;

    HLD(int n_, int r_) : n(n_), root(r_), adj(n_ + 1), sz(n_ + 1, 0), dep(n_ + 1, 0), fa(n_ + 1, 0), son(n_ + 1, 0), top(n_ + 1, 0) {}

    void addEdge(int u, int v) 
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs1(int u, int p, int d) 
    {
        dep[u] = d;
        fa[u] = p;
        sz[u] = 1;
        int max_sz = -1;
        for (int v : adj[u]) 
        {
            if (v == p) continue;
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > max_sz) 
            {
                max_sz = sz[v];
                son[u] = v;
            }
        }
    }

    void dfs2(int u, int t) 
    {
        top[u] = t;
        if (!son[u]) return;
        dfs2(son[u], t);
        for (int v : adj[u]) 
        {
            if (v != fa[u] && v != son[u])
                dfs2(v, v);
        }
    }

    void init() 
    {
        dfs1(root, 0, 1);
        dfs2(root, root);
    }

    int getLCA(int u, int v) 
    {
        while (top[u] != top[v]) 
        {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<vector<pll>> adj(n + 1);
    vector<int> dfn(n + 1, 0);

    HLD hld(n, 1);
    for (int i = 1; i < n;i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
        hld.addEdge(u, v);
    }
    int tot = 1;
    hld.init();
    vector<i64> dist(n + 1, 0);

    auto dfs = [&](auto self, int u, int p) -> void
    {
        dfn[u] = tot++;
        for(auto &[w, v] : adj[u])
        {
            if(v == p)
                continue;

            dist[v] = dist[u] + w;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    auto calc = [&](int u, int v) -> i64
    {
        int lca = hld.getLCA(u, v);
        return dist[u] + dist[v] - 2 * dist[lca];
    };

    set<pii> st;
    i64 ans = 0;
    auto getadj = [&](int x) -> pii
    {
        auto it = st.lower_bound({dfn[x], x});
        auto nxt = it;
        nxt++;
        if(nxt == st.end())
            nxt = st.begin();

        auto pre = it;
        if(pre == st.begin())
            pre = prev(st.end());
        else
            pre = prev(pre);

        return {pre->second, nxt->second};
    };

    for (int i = 0; i < n;i++)
    {
        int x, s;
        cin >> x >> s;
        if(st.count({dfn[x], x}))
        {
            auto [u, v] = getadj(x);
            debug(u)debug(v)
            st.erase({dfn[x], x});
            ans -= calc(u, x) + calc(x, v) - calc(u, v);
        }
        else
        {
            st.insert({dfn[x], x});
            auto [u, v] = getadj(x);
            ans += calc(u, x) + calc(x, v) - calc(u, v);
        }
        if(st.empty())
            cout << 0 << " ";   
        else if(st.count({dfn[s], s}))
            cout << ans << " ";
        else
        {
            st.insert({dfn[s], s});
            auto [u, v] = getadj(s);
            i64 res = ans + calc(u, s) + calc(s, v) - calc(u, v);
            cout << res << " ";
            st.erase({dfn[s], s});
        }
    }
    cout << "\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}