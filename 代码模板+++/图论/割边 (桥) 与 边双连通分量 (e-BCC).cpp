#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<int, int> pii;
struct EBCC
{
    int n;
    vector<vector<pii>> adj;
    vector<int> dfn, low, stk;
    int dfncnt, ebccnt, bridgecnt;
    vector<vector<int>> ebc;
    EBCC(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<pii>());
        dfn.assign(n + 1, 0);
        low.resize(n + 1, 0);
        stk.clear();
        ebc.clear();
        dfncnt = ebccnt = bridgecnt = 0;
    }
    
    void addEdge(int u, int v, int id)
    {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    void dfs(int u, int inEdge = 0)
    {
        dfn[u] = low[u] = ++dfncnt;
        stk.push_back(u);

        for(auto &[v, id] : adj[u])
        {
            if(!dfn[v])
            {
                dfs(v, id);
                low[u] = min(low[u], low[v]);

                if(low[v] > dfn[u])
                    bridgecnt++;
            }
            else if(id != inEdge)
            {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if(low[u] == dfn[u])
        {
            ebccnt++;
            vector<int> comp;
            while(1)
            {
                int x = stk.back();
                stk.pop_back();
                comp.push_back(x);
                if(x == u)
                    break;
            }
            ebc.push_back(comp);
        }
    }

    void work()
    {
        for (int i = 1; i <= n;i++)
        {
            if(!dfn[i])
            {
                stk.clear();
                dfs(i);
            }
        }
    }
};

