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
    vector<vector<int   >> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;
    SCC() {}
    SCC(int n_)
    {
        init(n_);
    }
    //注意这里是0 -index
    //如果题目为从1开始的点，我们在插入边的时候统一减一
    void init(int n_)
    {
        n = n_;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }
    //u -> v
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }
    void dfs(int x)
    {
        dfn[x] = low[x] = cur++;// 一进门，先领个时间戳，并且一开始能回溯到的最早时间就是自己
        stk.push_back(x);// 进栈，表示正在处理中，还没归属
        for(auto y : adj[x])
        {
            if(dfn[y] == -1)//// 如果邻居 y 还没被访问过
            {
                dfs(y);//往下搜
                // 等 y 搜完回来了，用 y 能到达的最早时间来更新 x，因为此时y已经完整跑完了dfs
                low[x] = min(low[x], low[y]);
            }
            else if(bel[y] == -1)
            {
                // 如果 y 访问过，且 bel[y] 是 -1，说明 y 还在栈里！
                // 这意味着 x 找到了一条“返祖边”连向了老祖宗 y，构成了环
                low[x] = min(low[x], dfn[y]);//我们用y的时间戳更新low[x],因为x可以往回到达y
            }
        }
        // 如果搜完一圈发现，自己能回溯到的最早节点就是自己
        // 说明自己就是这个“环/强连通分量”的最高点（根头目）
        if(dfn[x] == low[x])
        {
            int y;
            do{
                y = stk.back();// 把栈里在自己之上的兄弟全弹出来
                bel[y] = cnt;// 给他们统一下发同一个新的身份证号 cnt
                stk.pop_back();
            } while (y != x);// 直到把自己也弹出来为止
            cnt++;// 编号用完了，下一个环用新编号
        }
    }

    vector<int> work()
    {
        for (int i = 0;i < n;i++)
        {
            if(dfn[i] == -1)
                dfs(i);
        }
        return bel;
    }
};