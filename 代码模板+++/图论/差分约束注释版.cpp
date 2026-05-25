#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<long, long> pll;
struct DiffConstraint
{
    int n;

    vector<vector<pll>> adj;
    vector<i64> dist;
    vector<int> count;// 记录每个节点入队的次数，用于判负环
    vector<int> inQueue;// SPFA 的在队标记

    DiffConstraint(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<pll>());
        dist.assign(n + 1, 0);
        count.assign(n + 1, 0);
        inQueue.assign(n + 1, 0);
    }

    // 添加不等式约束：x_v - x_u <= w  (即 x_v <= x_u + w)
    // 对应图中从 u 连向 v，边权为 w 的有向边
    // 全宇宙唯一的加边接口：期望输入永远是 x_v - x_u <= w
    // 如果题目是 x_v - x_u >= w，请你自己取负，调用 addConstraint(v, u, -w)
    void addEdge(int u, int v, i64 w) 
    {
        adj[u].push_back({v, w});
    }

    // 求解差分约束系统。如果存在可行解，返回 true；若存在负权环导致无解，返回 false。
    bool sol()
    {
        queue<int> q;

        // 隐式超级源点思想：将所有节点初始入队，并将距离设为 0
        // 这相当于添加了约束 x_i <= 0，保证所有节点都能被约束网络触达
        for (int i = 1; i <= n;i++)
        {
            dist[i] = 0;
            inQueue[i] = 1;
            count[i] = 1;
            q.push(i);
        }

        // SPFA 核心引擎
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            inQueue[u] = 0;

            for(const auto &[v, w] : adj[u])
            {
                // 尝试松弛
                if(dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;

                    if(!inQueue[v])
                    {
                        q.push(v);
                        inQueue[v] = 1;
                        count[v]++;

                        // 判负环：在 n 个点的图中，任意两点间的最短路最多包含 n-1 条边
                        // 如果一个节点入队次数达到或超过 n 次，必然存在负权环
                        if(count[v] >= n)
                            return false;
                    }
                }
            }
        }
        return true;
    }
};