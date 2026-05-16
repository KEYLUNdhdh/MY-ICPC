#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const i64 INF = 2e18;

struct Dinic
{
    struct Edge
    {
        int to;
        i64 cap;
        i64 flow;
        int rev;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> ptr;

    Dinic () {}
    Dinic(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<Edge>());
        level.resize(n + 1);
        ptr.resize(n + 1);
    }

    void addEdge(int from, int to , i64 cap)
    {
        adj[from].push_back({to, cap, 0, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
    }

    bool bfs(int s, int t)
    {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for(auto &[to, cap, flow, rev] : adj[u])
            {
                if(cap - flow > 0 && level[to] == -1)
                {
                    level[to] = level[u] + 1;
                    q.push(to);
                }
            }
        }

        return level[t] != -1;
    }

    i64 dfs(int v, int t, i64 pushed)
    {
        if(pushed == 0)
            return 0;
        if(v == t)
            return pushed;

        for (int &cid = ptr[v]; cid < adj[v].size(); cid++)
        {
            auto &[to, cap, flow, rev] = adj[v][cid];
            int tr = to;

            if(level[v] + 1 != level[tr] || cap - flow == 0)
                continue;

            i64 push = dfs(tr, t, min(pushed, cap - flow));
            if(push == 0)
                continue;

            flow += push;
            adj[tr][rev].flow -= push;
            return push;
        }
        return 0;
    }

    i64 maxFlow(int s, int t)
    {
        i64 flow = 0;
        while(bfs(s, t))
        {
            fill(ptr.begin(), ptr.end(), 0);

            while(i64 pushed = dfs(s, t, INF))
                flow += pushed;
        }
        return flow;
    }
};