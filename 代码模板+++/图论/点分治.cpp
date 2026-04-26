#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct PointDiv
{
    struct Edge
    {
        int to, weight;
    };

    int n, k;
    vector<vector<Edge>> adj;
    vector<int> siz, maxp, vis;
    int root, totalSize;

    vector<int> queries, ans;

    vector<int> judge, curDis, allDis;

    PointDiv(int n_, const vector<int> &q, int MAXK) : n(n_), queries(q), k(MAXK)
    {
        adj.resize(n + 1);
        siz.resize(n + 1);
        maxp.resize(n + 1);
        vis.resize(n + 1);
        ans.resize(queries.size(), 0);

        judge.resize(MAXK + 1, 0);
    }

    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void getRoot(int u, int p)
    {
        siz[u] = 1;
        maxp[u] = 0;
        for(const auto &e : adj[u])
        {
            int v = e.to;
            if(v == p || vis[v])
                continue;
            getRoot(v, u);
            siz[u] += siz[v];
            maxp[u] = max(maxp[u], siz[v]);
        }
        maxp[u] = max(maxp[u], totalSize - siz[u]);
        if(root == 0 || maxp[u] < maxp[root])
            root = u;
    }

    void getDist(int u, int p, int d)
    {
        if(d > k)
            return;
        curDis.push_back(d);
        for(const auto &e : adj[u])
        {
            int v = e.to;
            int w = e.weight;
            if(v == p || vis[v])
                continue;
            getDist(v, u, d + w);
        }
    }

    void calc(int u)
    {
        allDis.clear();
        judge[0] = 1;

        for(const auto &e : adj[u])
        {
            int v = e.to;
            int w = e.weight;
            if(vis[v])
                continue;
            curDis.clear();
            getDist(v, u, w);

            for(int d : curDis)
            {
                for (int i = 0; i < queries.size(); i++)
                {
                    if(ans[i])
                        continue;
                    if(queries[i] >= d && judge[queries[i] - d])
                        ans[i] = 1;
                }
            }
            for(int d : curDis)
            {
                judge[d] = 1;
                allDis.push_back(d);
            }
        }

        for(int d : allDis)
        {
            judge[d] = 0;
        }
    }

    void sol(int u)
    {
        vis[u] = 1;
        calc(u);

        for (const auto &e : adj[u])
        {
            int v = e.to;
            if(vis[v])
                continue;
            totalSize = siz[v];
            root = 0;
            getRoot(v, 0);
            sol(root);
        }
    }

    vector<int> run()
    {
        totalSize = n;
        root = 0;
        getRoot(1, 0);
        sol(root);
        return ans;
    }
};