#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int P = 998244353;
struct SegmentTree
{
    int n;
    vector<i64> sum, lazy;

    SegmentTree(int n_) : n(n_), sum(4 * n + 1, 0), lazy(4 * n + 1, 0){}

    void pull(int p)
    {
        sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % P;
    }

    void apply(int p, int l, int r, i64 v)
    {
        sum[p] = (sum[p] + v * (r - l + 1)) % P;
        lazy[p] = (lazy[p] + v) % P;
    }

    void push(int p, int l, int r)
    {
        if(lazy[p])
        {
            int m = l + r >> 1;
            apply(p << 1, l, m, lazy[p]);
            apply(p << 1 | 1, m + 1, r, lazy[p]);
            lazy[p] = 0;
        }
    }

    void build(int p, int l, int r, const vector<i64> &a)
    {
        if(l >= r)
        {
            sum[p] = a[l] % P;
            return;
        }

        int m = l + r >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        pull(p);
    }

    void build(const vector<i64> &a)
    {
        build(1, 1, n, a);
    }
    
    void rangeAdd(int p, int l, int r, int x, int y, i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            apply(p, l, r, v);
            return;
        }
        push(p, l, r);
        int m = l + r >> 1;
        rangeAdd(p << 1, l, m, x, y, v);
        rangeAdd(p << 1 | 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeAdd(int x, int y, i64 v)
    {
        v %= P;
        rangeAdd(1, 1, n, x, y, v);
    }

    i64 rangeQuery(int p,int l, int r, int x, int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return sum[p];
        push(p, l, r);
        int m = r + l >> 1;
        return (rangeQuery(p << 1, l, m, x, y) + rangeQuery(p << 1 | 1, m + 1, r, x, y)) % P;
    }

    i64 rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y) % P;
    }
};

struct HLD
{
    int n, root, timer;
    vector<vector<int>> adj;
    vector<int> sz, dep, fa, son, top, dfn, rnk;
    vector<i64> val, mapped_val;
    SegmentTree seg;

    HLD(int n_, int r_) : n(n_), root(r_), timer(0), adj(n_ + 1), sz(n_ + 1, 0), dep(n_ + 1, 0), fa(n_ + 1, 0), son(n_ + 1, 0), top(n_ + 1, 0), dfn(n_ + 1, 0), rnk(n_ + 1, 0), val(n_ + 1, 0), mapped_val(n_ + 1, 0), seg(n_) {}

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
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if(sz[v] > max_sz)
            {
                max_sz = sz[v];
                son[u] = v;
            }
        }
    }

    void dfs2(int u, int t)
    {
        dfn[u] = ++timer;
        rnk[timer] = u;
        top[u] = t;
        mapped_val[timer] = val[u];
        if(!son[u])
            return;
        dfs2(son[u], t);

        for(int v : adj[u])
        {
            if (v != fa[u] && v != son[u])
                dfs2(v, v);
        }
    }

    void init()
    {
        dfs1(root, 0, 1);
        dfs2(root, root);
        seg.build(mapped_val);
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
    
    void modifyPath(int u, int v, i64 w)
    {
        w %= P;
        while(top[u] != top[v])
        {
            if(dep[top[u]] < dep[top[v]])
                swap(u, v);
            seg.rangeAdd(dfn[top[u]], dfn[u], w);
            u = fa[top[u]];
        }

        if(dep[u] > dep[v])
            swap(u, v);
        seg.rangeAdd(dfn[u], dfn[v], w);
    }

    i64 queryPath(int u, int v)
    {
        i64 res = 0;
        while(top[u] != top[v])
        {
            if(dep[top[u]] < dep[top[v]])
                swap(u, v);
            res = (res + seg.rangeQuery(dfn[top[u]], dfn[u])) % P;
            u = fa[top[u]];
        }

        if(dep[u] > dep[v])
            swap(u, v);
        res = (res + seg.rangeQuery(dfn[u], dfn[v])) % P;
        return res;
    }

    void modifySubtree(int u, i64 w)
    {
        w %= P;
        seg.rangeAdd(dfn[u], dfn[u] + sz[u] - 1, w);
    }

    i64 querySubtree(int u)
    {
        return seg.rangeQuery(dfn[u], dfn[u] + sz[u] - 1);
    }
};