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

// 改造后的无源汇上下界可行流 (Bounded Circulation)
struct BoundedCirculation
{
    int n;
    int S, T; // 这里的S和T是附加的超级源点和超级汇点，用来补齐下界流量

    Dinic dinic;
    vector<i64> delta;
    i64 sumLower;

    BoundedCirculation(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        S = 0;
        T = n + 1;

        dinic.init(T);
        delta.assign(n + 2, 0);
        sumLower = 0;
    }

    // 添加一条 u -> v 的边，流量限制为 [l, r]
    void addEdge(int u, int v, i64 l, i64 r)
    {
        dinic.addEdge(u, v, r - l); // 真实网络中建图容量为 r - l
        delta[v] += l;              // 记录盈亏
        delta[u] -= l;
    }

    // 判断是否存在可行流
    bool sol()
    {
        for (int i = 1; i <= n; i++)
        {
            if(delta[i] > 0)
            {
                dinic.addEdge(S, i, delta[i]);
                sumLower += delta[i];
            }
            else if (delta[i] < 0)
            {
                dinic.addEdge(i, T, -delta[i]);
            }
        }

        // 如果超级源点到超级汇点的最大流等于所有下界之和，则说明可行
        return dinic.maxFlow(S, T) == sumLower;
    }
};

