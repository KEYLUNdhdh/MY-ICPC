#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct DSUonTree
{
    int n;
    vector<vector<int>> adj;
    vector<int> color;
    vector<int> sz, son;

    vector<int> cnt;
    int maxcnt;
    i64 sumcolor;
    vector<i64> ans;
    int skip;

    DSUonTree(int n_, const vector<int> &c) : n(n_), color(c)
    {
        adj.resize(n + 1);
        sz.resize(n + 1, 0);
        son.resize(n + 1, 0);

        cnt.resize(n + 1, 0);
        ans.resize(n + 1, 0);
        maxcnt = 0;
        sumcolor = 0;
        skip = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfsSz(int u, int p)
    {
        sz[u] = 1;
        int maxsub = 0;
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            dfsSz(v, u);
            sz[u] += sz[v];
            if(sz[v] > maxsub)
            {
                maxsub = sz[v];
                son[u] = v;
            }
        }
    }

    void add(int u, int p, int val)
    {
        
    }
};