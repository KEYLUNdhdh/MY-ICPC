#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct VirtualTree
{
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, dep;
    vector<vector<int>> st;
    int timer;

    vector<vector<int>> vtadj;
    vector<int> vtnodes;

    VirtualTree(int n_) : n(n_)
    {
        adj.resize(n + 1);
        vtadj.resize(n + 1);
        dfn.resize(n + 1, 0);
        dep.resize(n + 1, 0);
        st.assign(20, vector<int>(n + 1, 0));
        timer = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p, int d)
    {
        dfn[u] = ++timer;
        dep[u] = d;
        st[0][u] = p;
        for (int i = 1; i < 20;i++)
            st[i][u] = st[i - 1][st[i - 1][u]];
        for(int v : adj[u])
        {
            if(v != p)
                dfs(v, u, d + 1);
        }
    }

    void init(int root = 1)
    {
        dfs(root, 0, 1);
    }

    int getLCA(int u, int v)
    {
        if(dep[u] < dep[v])
            swap(u, v);
        for (int i = 19; i >= 0; i--)
        {
            if(dep[st[i][u]] >= dep[v])
                u = st[i][u];
        }

        if(u == v)
            return u;

        for (int i = 19; i >= 0;i--)
        {
            if(st[i][u] != st[i][v])
            {
                u = st[i][u];
                v = st[i][v];
            }
        }
        return st[0][u];
    }

    int build(vector<int> nodes)
    {
        if(nodes.empty())
            return 0;
        sort(nodes.begin(), nodes.end(), [&](int u, int v)
             { return dfn[u] < dfn[v]; });

        int k = nodes.size();
        for (int i = 0; i < k - 1;i++)
            nodes.push_back(getLCA(nodes[i], nodes[i + 1]));

        sort(nodes.begin(), nodes.end(), [&](int u, int v)
             { return dfn[u] < dfn[v]; });

        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        vtnodes = nodes;

        for (int i = 1; i < nodes.size();i++)
        {
            int p = getLCA(nodes[i - 1], nodes[i]);
            vtadj[p].push_back(nodes[i]);
        }

        return nodes[0];
    }

    void clear()
    {
        for(int u : vtnodes)
            vtadj[u].clear();
        vtnodes.clear();
    }
};