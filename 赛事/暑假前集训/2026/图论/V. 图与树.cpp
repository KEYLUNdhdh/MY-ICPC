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

struct DSU
{
    vector<int> f, siz;
    int part;
    DSU() {};
    DSU(int n)
    {
        init(n);
    }
    //input n,open n + 1
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        part = n;
    }
    int find(int x)
    {
        while(x != f[x])
            x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(siz[x] < siz[y])
            swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        part--;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};

struct edge
{
    int u, v, w;

    bool operator<(const edge b) const
    {
        return w < b.w;
    };
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pll>> adj(n + 1);
    vector<edge> edges;
    vector<int> added(m, 0);
    for (int i = 0; i < m;i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    HLD hld(n, 1);
    for (int i = 0; i < m;i++)
    {
        auto &[u, v, w] = edges[i];
        int fu = dsu.find(u);
        int fv = dsu.find(v);
        if(fu == fv)
            continue;

        dsu.merge(u, v);
        hld.addEdge(u, v);
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
        added[i] = 1;

        if(dsu.part == 1)
            break;
    }
    hld.init();
    vector<i64> dist(n + 1, 0);

    auto dfs = [&](auto self, int u, int p) -> void
    {
        for(auto [w, v] : adj[u])
        {
            if(v == p)
                continue;
            dist[v] = dist[u] + w;
            self(self, v, u);
        }
    };

    dfs(dfs, 1, 0);

    for (int i = 0; i < m;i++)
    {
        if(added[i])
            continue;

        auto &[u, v, w] = edges[i];
        int fa = hld.getLCA(u, v);
        i64 dis = dist[u] + dist[v] - 2 * dist[fa];
        if(dis > w)
        {
            cout << "No";
            return;
        }
    }
    cout << "Yes";
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