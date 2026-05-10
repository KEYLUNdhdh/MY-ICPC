#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
//有向图中求强连通分量的 Tarjan 算法
//dfn (DFS Number)：时间戳数组。记录每个节点在 DFS 遍历时第一次被访问到的顺序（第几个被发现的）。
// low (Lowest value)：追溯值数组。记录当前节点通过它的邻居（包括后代），能够“绕”回到的最早的时间戳（你能回到的最早祖先是谁）。
//bel (Belong)：归属数组。这就是缩点后的结果！它记录了原图中的每个点，最终被打包到了哪一个“强连通分量（大胖点）”里。相当于它们在新图里的“新身份证号”。
//stk (Stack栈)：用来保存在当前搜索路径上，且还没有被确立归属的节点。
//cur：时间戳发号器（从 0 开始递增）。
//cnt：强连通分量的计数器（最终 cnt 的值就是缩点后新图的节点总数）。
//O(n + m)
struct SCC
{
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;
    
    SCC() {}
    SCC(int n_) { init(n_); }
    
    // 1-index
    //我们缩点后的大的点也从1 -index开始
    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<int>()); // 开 n+1 的空间
        dfn.assign(n + 1, 0);             // 0 表示未访问
        low.resize(n + 1);
        bel.assign(n + 1, 0);             // 0 表示还未分配到任何 SCC 中
        stk.clear();
        cur = cnt = 1;                    // 时间戳和连通分量编号都从 1 开始
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void dfs(int x)
    {
        dfn[x] = low[x] = cur++; // 刚来这座城市，发时间戳。目前最老只能回到自己。
        stk.push_back(x);        // 住进客栈

        for(auto y : adj[x])
        {
            if(!dfn[y]) // 发现一座从未去过的新城市
            {
                dfs(y);// 派人去探索 y
                // y 探索回来了。如果 y 找到了通往远古时期的暗道，x 借着 y 的光，也能回去！
                low[x] = min(low[x], low[y]);
            }
            else if(!bel[y]) // y 以前去过，而且 y 还在客栈里！说明发现了一条“返祖边”（形成环了）！
            {
                // 直接借用 y 的时间戳，更新 x 的时光机
                low[x] = min(low[x], dfn[y]);
            }
        }

        // 探索完所有邻居后，结算！
        if(dfn[x] == low[x])
        {
            int y;
            do {
                y = stk.back();// 把客栈最顶上的人赶出来
                bel[y] = cnt; // 给他们发同一个圈子的编号
                stk.pop_back();
            } while (y != x);// 一直赶，直到把 x 自己也赶出来为止
            cnt++;// 圈子总数 + 1
        }
    }

    vector<int> work()
    {
        for (int i = 1; i <= n; i++) // 1-index 遍历
        {
            if(!dfn[i])
                dfs(i);
        }
        return bel;
    }
};