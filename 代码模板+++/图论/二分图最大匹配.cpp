#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr i64 MOD = 998244353, INF = 1e9;

struct Dinic
{
    struct Edge
    {
        int to;
        int cap;
        int flow;
        int rev;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> ptr;

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

    void addEdge(int from, int to , int cap)
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

    int dfs(int v, int t, int pushed)
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

            int push = dfs(tr, t, min(pushed, cap - flow));
            if(push == 0)
                continue;

            flow += push;
            adj[tr][rev].flow -= push;
            return push;
        }
        return 0;
    }

    int maxFlow(int s, int t)
    {
        int flow = 0;
        while(bfs(s, t))
        {
            fill(ptr.begin(), ptr.end(), 0);

            while(int pushed = dfs(s, t, INF))
                flow += pushed;
        }
        return flow;
    }
};

void solve()
{
    int n, m, e;
    cin >> n >> m >> e;

    int s = 0;// 超级源点 S 的身份证号
    int t = n + m + 1;// 超级汇点 T 的身份证号
    Dinic dinic(t);// 告诉 Dinic 引擎，图中最大的编号是 t

    // 1. 超级源点 S 连接所有左部点，容量为 1
    for (int i = 1; i <= n;i++)
    {
        dinic.addEdge(s, i, 1);
    }

    // 2. 所有右部点连接超级汇点 T，容量为 1
    for (int i = 1; i <= m;i++)
    {
        dinic.addEdge(n + i, t, 1);
    }

    // 3. 读取边，连接左右部点
    for (int i = 0; i < e;i++)
    {
        int u, v;
        cin >> u >> v;
        // 左部点 u，右部点 v (为了避免编号冲突，右部点编号加上 n)
        // 即使有重边也没关系，最大流算法会自动处理
        dinic.addEdge(u, n + v, 1);
    }

    // 输出最大匹配数（即最大流）
    cout << dinic.maxFlow(s, t) << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}