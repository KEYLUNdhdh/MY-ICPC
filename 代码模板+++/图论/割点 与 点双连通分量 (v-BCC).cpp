#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct VBCC
{
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, low, isCut, stk;
    int dfncnt, vbccnt, cutcnt;
    vector<vector<int>> vbc;

    VBCC(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<int>());
        dfn.assign(n + 1, 0);
        low.resize(n + 1);
        isCut.assign(n + 1, 0);
        stk.clear();
        vbc.clear();
        dfncnt = vbccnt = cutcnt = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p = 0)
    {
        dfn[u] = low[u] = ++dfncnt;
        stk.push_back(u);
        int child = 0;

        if(p == 0 && adj[u].empty())
        {
            vbccnt++;
            stk.pop_back();
            vbc.push_back({u});
            return;
        }

        for(int v : adj[u])
        {
            if(!dfn[v])
            {
                child++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);

                if(low[v] >= dfn[u])
                {
                    isCut[u] = 1;
                    vbccnt++;
                    vector<int> comp;
                    while(1)
                    {
                        int x = stk.back();
                        stk.pop_back();
                        comp.push_back(x);
                        if(x == v)
                            break;
                    }
                    comp.push_back(u);
                    vbc.push_back(comp);
                }
            }
            else if(v != p)
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(p == 0 && child < 2)
            isCut[u] = 0;
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
        for (int i = 1; i <= n;i++)
        {
            if(isCut[i])
                cutcnt++;
        }
    }
};