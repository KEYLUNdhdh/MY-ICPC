#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<i64, i64> pll;

const i64 INF = 2e18;// 费用可能很大，必须用 1e18 级别的无穷大

struct MCFGraph
{
    struct Edge
    {
        int to;
        i64 cap;
        i64 flow;
        i64 cost;// 增加了：单位流量的费用
        int rev;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<i64> h;// 核心魔法：顶点的势能 (Potential)
    vector<i64> dist;// Dijkstra 用的距离数组
    vector<int> prevV;// 记录最短路上的前驱顶点
    vector<int> prevE;// 记录最短路上的前驱边索引

    MCFGraph() {}
    MCFGraph(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<Edge>());
        h.assign(n + 1, 0);
        dist.resize(n + 1, 0);
        prevV.resize(n + 1);
        prevE.resize(n + 1);
    }

    void addEdge(int from, int to, i64 cap, i64 cost)
    {
        // 正向边：容量为 cap，费用为 cost
        adj[from].push_back({to, cap, 0, cost, (int)adj[to].size()});
        // 反向边：容量为 0，费用为 -cost (反悔退钱！)
        adj[to].push_back({from, 0, 0, -cost, (int)adj[from].size() - 1});
    }

    // 返回值：{最大流, 最小费用}
    pll work(int s, int t)
    {
        i64 maxFlow = 0;
        i64 minCost = 0;

        while(1)
        {
            // 1. 跑带势能的 Dijkstra，寻找最便宜的增广路
            // 优先队列存 pair<距离, 节点>，小根堆
            priority_queue<pll, vector<pll>, greater<pll>> pq;

            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            pq.push({0, s});

            while(!pq.empty())
            {
                auto [d, u] = pq.top();
                pq.pop();

                if(dist[u] < d)// 懒惰删除法
                    continue;

                for (int i = 0; i < adj[u].size(); i++)
                {
                    auto &[to, cap, flow, cost, rev] = adj[u][i];
                    // 必须有剩余容量
                    if(cap - flow > 0)
                    {
                        // 核心：等效边权（Reduced Cost）= edge.cost + h[u] - h[to]
                        i64 reducedCost = cost + h[u] - h[to];

                        if(dist[to] > dist[u] + reducedCost)
                        {
                            dist[to] = dist[u] + reducedCost;
                            prevV[to] = u;// 记录路径，方便一会退水
                            prevE[to] = i;
                            pq.push({dist[to], to});
                        }
                    }
                }
            }

            // 如果连汇点都走不到了，说明已经达到最大流，结束
            if(dist[t] == INF)
                break;

            // 2. 极为关键的一步：更新全部节点的势能
            for (int i = 1; i <= n;i++)
            {
                if(dist[i] != INF)
                    h[i] += dist[i];
            }

            // 3. 顺着记录的路径，找这条路上的“木桶短板”（最大可增广流量）
            i64 push = 2e18;// 初始化为无穷大
            for (int v = t; v != s; v = prevV[v])
            {
                int u = prevV[v];
                int idx = prevE[v];
                push = min(push, adj[u][idx].cap - adj[u][idx].flow);
            }

            // 4. 真正开始流水：更新流量与总费用
            maxFlow += push;

            // 因为 h[t] 恰好等于当前从 s 到 t 的真实最短路长度，所以直接乘！
            minCost += push * h[t];

            for (int v = t; v != s; v=  prevV[v])
            {
                int u = prevV[v];
                int idx = prevE[v];
                int rev = adj[u][idx].rev;

                adj[u][idx].flow += push;
                adj[v][rev].flow -= push;// 反向边容量增加（允许反悔）
            }
        }
        return {maxFlow, minCost};
    }
};