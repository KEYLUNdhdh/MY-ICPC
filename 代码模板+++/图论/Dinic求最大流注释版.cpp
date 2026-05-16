#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int INF = 1e9;

struct Dinic
{
    // 定义一条有向边
    struct Edge
    {
        int to;// 指向的节点
        int cap;// 管道容量 (Capacity)
        int flow;// 当前流量 (Flow)
        int rev;// 反向边在目标节点邻接表中的索引 (用于快速反悔)
    };

    int n;
    vector<vector<Edge>> adj;// 邻接表存图
    vector<int> level;// 节点的层次 (BFS 距离)
    vector<int> ptr;// 当前弧优化指针 (DFS 用)

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

    // 添加一条从 from 到 to，容量为 cap 的有向边
    void addEdge(int from, int to , int cap)
    {

        // 正向边：初始容量为 cap，流量为 0
        adj[from].push_back({to, cap, 0, (int)adj[to].size()});

        // 反向边：初始容量为 0，流量为 0。这是网络流“反悔机制”的核心！
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
    }

    // BFS：给图分层，判断还能不能从源点 s 流到汇点 t
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
                // 如果管道还没满，且目标节点还没被分层
                if(cap - flow > 0 && level[to] == -1)
                {
                    level[to] = level[u] + 1;// 目标节点在下一层
                    q.push(to);
                }
            }
        }
        // 如果汇点 t 被分到了层数，说明还有路可走，返回true
        return level[t] != -1;
    }

    // DFS：在层次图上寻找增广路，狠狠地注水！
    // pushed 表示当前带着多少水流过来
    int dfs(int v, int t, int pushed)
    {
        if(pushed == 0)
            return 0;
        if(v == t)
            return pushed;// 到达终点，成功把水送达！

        // ptr[v] 是当前弧优化：如果前面的边已经榨干了，下次来就不看它们了，直接从 ptr[v] 开始看
        for (int &cid = ptr[v]; cid < adj[v].size(); cid++)
        {
            auto &[to, cap, flow, rev] = adj[v][cid];
            int tr = to;

            // 必须严格往下一层流 (不走回头路)，且管道必须有剩余容量
            if(level[v] + 1 != level[tr] || cap - flow == 0)
                continue;

            // 递归往下送水，送水量不能超过当前管道的剩余容量
            int push = dfs(tr, t, min(pushed, cap - flow));
            if(push == 0)
                continue;

            // 重点：水送成功了，更新正向边和反向边的流量
            flow += push;
            adj[tr][rev].flow -= push;// 反向边流量减少（相当于给了程序反悔把水抽回来的机会）
            return push;
        }
        return 0;// 这条路死胡同，送不出去
    }

    // 主函数：计算最大流
    int maxFlow(int s, int t)
    {
        int flow = 0;

        // 只要 BFS 还能给汇点分层（说明还有路）
        while(bfs(s, t))
        {
            fill(ptr.begin(), ptr.end(), 0);// 每次重新分层后，清空当前弧优化指针

            // 不断 DFS 找路，直到当前层次图里再也榨不出水为止
            while(int pushed = dfs(s, t, INF))
                flow += pushed;
        }
        return flow;
    }
};