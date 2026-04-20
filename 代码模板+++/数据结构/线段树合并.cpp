#include  <bits/stdc++.h>
using namespace std;
using i64 = long long;

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