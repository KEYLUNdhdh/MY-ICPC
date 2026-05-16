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

struct BoundedMaxFlow
{
    int n, s, t;
    int S, T;// 内部的超级源点 SS 和超级汇点 TT

    Dinic dinic;// 底层调用的标准 Dinic 引擎
    vector<i64> delta;// 记录每个节点“流入下界和 - 流出下界和”的盈亏差值
    i64 sumLower;// 记录所有保底水量的总和，用来校验是否满流

    BoundedMaxFlow(int n_, int s_, int t_)
    {
        init(n_, s_, t_);
    }

    void init(int n_, int s_, int t_)
    {
        n = n_;
        s = s_;
        t = t_;
        S = 0;// 超级源点分配编号 0
        T = n + 1;// 超级汇点分配编号 n + 1

        dinic.init(T);// 底层引擎的节点编号上限是 T
        delta.assign(n + 2, 0);
        sumLower = 0;   
    }

    // 核心接口：添加一条带有流量下界 l 和上界 r 的边
    void addEdge(int u, int v, i64 l, i64 r)
    {
        // 1. 保底：直接截留 l 的容量，真正的管道里只放 r - l 的剩余容量
        dinic.addEdge(u, v, r - l);

        // 2. 记账：v 被强制塞入了 l 的水（盈余），u 被强制抽走了 l 的水（亏损）
        delta[v] += l;
        delta[u] -= l;
    }

    // 求解最大流，如果无解返回 -1
    i64 sol()
    {
        // 1. 调平阶段：根据盈亏账本，连接超级源汇，构建附加网络
        for (int i = 1; i <= n;i++)
        {
            if(delta[i] > 0)
            {
                dinic.addEdge(S, i, delta[i]);// 盈余节点：把水排给超级源点 (这里等效处理)
                sumLower += delta[i];// 统计总共需要补偿多少水
            }
            else if (delta[i] < 0)
            {
                dinic.addEdge(i, T, -delta[i]);// 亏损节点：从超级汇点抽水补齐
            }
        }

        // 把原汇点 t 和原源点 s 连起来，容量无穷大，让水能循环流通
        dinic.addEdge(t, s, INF);

        // 记录这条 t -> s 虚拟边在 t 的邻接表里的位置，一会要拆桥
        int tsIdx = dinic.adj[t].size() - 1;

        // 2. 跑第一次 Dinic：从超级源点 S 到超级汇点 T 测底细
        i64 flow1 = dinic.maxFlow(S, T);

        // 如果补偿的水量没达到要求，说明根本没法满足所有边的保底下界，原图无解！
        if(flow1 != sumLower)
            return -1;

        // 3. 榨干阶段：可行流已经建立，底细摸清了
        // 原图中已经流过去的“保底水量”，刚好就是那条虚拟 t -> s 管道里流过的水
        i64 baseFlow = dinic.adj[t][tsIdx].flow;

        // 过河拆桥：把 t -> s 及其反向边彻底切断（容量和流量都清零）
        dinic.adj[t][tsIdx].cap = 0;
        dinic.adj[t][tsIdx].flow = 0;
        int stIdx = dinic.adj[t][tsIdx].rev;
        dinic.adj[s][stIdx].cap = 0;
        dinic.adj[s][stIdx].flow = 0;

        // 在残余网络上，从真正的源点 s 到真正的汇点 t 跑第二次 Dinic，把潜力榨干
        i64 extraFlow = dinic.maxFlow(s, t);

        // 最终最大流 = 保底水流 + 榨出来的额外水流
        return baseFlow + extraFlow;
    }
};