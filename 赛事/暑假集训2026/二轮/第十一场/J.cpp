#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x)                          \
    {                                     \
        cerr << #x << " = " << x << "\n"; \
    }
#define debugarr(x)           \
    {                         \
        cerr << #x << " : ";  \
        for (auto v : x)      \
            cerr << v << " "; \
        cerr << "\n";         \
    }
#define cutline                             \
    {                                       \
        cerr << "----------------------\n"; \
    }
using namespace std;
using i64 = long long;
const int MAXC = 100005;
template <class T>
void chmin(T &a, T b)
{
    if (a > b)
        a = b;
}
template <class T>
void chmax(T &a, T b)
{
    if (a < b)
        a = b;
}

typedef pair<int, int> pii;

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
            if (v == p)
                continue;
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
        if (!son[u])
            return;
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
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    HLD hld(n, 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        hld.addEdge(u, v);
    }
    hld.init();

    vector<int> dfn(n + 1, 0);
    int tot = 1;
    auto dfs = [&](auto self, int u, int p) -> void
    {
        dfn[u] = tot++;
        for (int v : adj[u])
        {
            if (v == p)
                continue;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);

    vector<int> col(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> col[i];
    }

    auto calc = [&](int u, int v) -> i64
    {
        int lca = hld.getLCA(u, v);
        return (i64)hld.dep[u] + hld.dep[v] - 2 * hld.dep[lca];
    };

    vector<set<pii>> st(MAXC);
    vector<i64> ans(MAXC, 0);

    // 获取按 dfs 序排布时，节点 x 在集合 c 中的前驱和后继 (首尾相连)
    auto getadj = [&](int x, int c) -> pii
    {
        auto it = st[c].lower_bound({dfn[x], x});
        auto nxt = it;
        nxt++;
        if (nxt == st[c].end())
            nxt = st[c].begin();

        auto pre = it;
        if (pre == st[c].begin())
            pre = prev(st[c].end());
        else
            pre = prev(pre);

        return {pre->second, nxt->second};
    };

    auto add_node = [&](int x, int c)
    {
        st[c].insert({dfn[x], x});
        auto [u, v] = getadj(x, c);
        ans[c] += calc(u, x) + calc(x, v) - calc(u, v);
    };

    auto del_node = [&](int x, int c)
    {
        auto [u, v] = getadj(x, c);
        st[c].erase({dfn[x], x});
        ans[c] -= calc(u, x) + calc(x, v) - calc(u, v);
    };

    for (int i = 1; i <= n; i++)
    {
        add_node(i, col[i]);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        char op;
        cin >> op;
        if (op == 'U')
        {
            int x, y;
            cin >> x >> y;
            del_node(x, col[x]);
            col[x] = y;
            add_node(x, col[x]);
        }
        else if (op == 'Q')
        {
            int y;
            cin >> y;
            if (st[y].empty())
                cout << -1 << "\n";
            else
                cout << ans[y] / 2 << "\n";
        }
    }
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    while (T--)
        solve();

    return 0;
}