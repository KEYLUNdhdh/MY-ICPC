#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline {cerr << "----------------------\n";}

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
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) // PII 
{
    return os << "(" << p.first << ", " << p.second << ")\n";
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) //vector
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &d) //deque
{
    os << "[";
    for (int i = 0; i < d.size(); ++i)
    {
        if (i)
            os << ", ";
        os << d[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &v) //set
{
    os << "[";
    for (auto x = v.begin(); x != v.end(); x++)
    {
        if (x != v.begin())
            os << ", ";
        os << *x;
    }
    return os << "]\n";
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const map<T1, T2> &v) //map
{
    os << " {";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << "(" << it->first << " -> " << it->second << ")"; //键值对
    }
    return os << "}\n";
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
constexpr int MOD = 998244353, INF = 1e9;
constexpr int MAXZ = 1e5 + 5;
struct DynamicSegmentTree
{
    int tot;
    vector<int> ls, rs, maxx, maxId;

    DynamicSegmentTree(int maxNodes):tot(0), ls(maxNodes, 0), rs(maxNodes, 0), maxx(maxNodes, 0), maxId(maxNodes, 0) {}

    void pull(int p)
    {
        if(maxx[ls[p]] >= maxx[rs[p]])
        {
            maxx[p] = maxx[ls[p]];
            maxId[p] = maxId[ls[p]];
        }
        else
        {
            maxx[p] = maxx[rs[p]];
            maxId[p] = maxId[rs[p]];
        }
    }

    void update(int &p, int l, int r, int pos, int val)
    {
        if(!p)
            p = ++tot;
        if(l == r)
        {
            maxx[p] += val;
            maxId[p] = (maxx[p] > 0) ? l : 0;
            return;
        }
        int m = l + r >> 1;
        if (pos <= m)
            update(ls[p], l, m, pos, val);
        else
            update(rs[p], m + 1, r, pos, val);
        pull(p);
    }

    int merge(int p, int q, int l, int r)
    {
        if(!p || !q)
            return p | q;
        if(l == r)
        {
            maxx[p] += maxx[q];
            maxId[p] = (maxx[p] > 0) ? l : 0;
            return p;
        }

        int m = l + r >> 1;
        ls[p] = merge(ls[p], ls[q], l, m);
        rs[p] = merge(rs[p], rs[q], m + 1, r);
        pull(p);
        return p;
    }  
};

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
    int n, m;
    cin >> n >> m;
    HLD hld(n, 1);

    for (int i = 1; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        hld.addEdge(u, v);
    }
    hld.init();

    DynamicSegmentTree sg(m * 80);
    vector<int> root(n + 1, 0);

    for (int i = 0; i < m;i++)
    {
        int u, v, z;
        cin >> u >> v >> z;
        int lca = hld.getLCA(u, v);
        int falca = hld.fa[lca];

        sg.update(root[u], 1, MAXZ, z, 1);
        sg.update(root[v], 1, MAXZ, z, 1);
        sg.update(root[lca], 1, MAXZ, z, -1);
        if(falca != 0)
        {
            sg.update(root[falca], 1, MAXZ, z, -1);
        }
    }

    vector<int> ans(n + 1, 0);
    auto dfs = [&](auto self, int u, int p) -> void
    {
        for(int v : hld.adj[u])
        {
            if(v == p)
                continue;
            self(self, v, u);
            root[u] = sg.merge(root[u], root[v], 1, MAXZ);
        }
        ans[u] = sg.maxId[root[u]];
    };

    dfs(dfs, 1, 0);

    for (int i = 1; i <= n;i++)
        cout << ans[i] << "\n";
    
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