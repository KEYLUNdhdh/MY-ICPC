#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct VBCC
{
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, low, isCut, stk;
    // dfn[u]：时间戳。表示在深度优先搜索（DFS）时，第几个访问到城市 u。它是一个绝对递增的序号。
    // low[u]：时光机。表示从城市 u 出发，在不走回头路的前提下，通过自己或者自己的子孙，能“穿越”回到的时间戳最小（也就是最老、最靠近根）的城市的 dfn 值。
    // stk：历史客栈（栈）。用来按顺序暂存我们走过的城市，方便后面把它们打包成一个 v-BCC。
    vector<vector<int>> vbc;//记录每个双连通分量内部的节点
    int dfncnt, vbccnt, cutcnt;

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
        dfn[u] = low[u] = ++dfncnt;// 刚到这座城市，时间戳发给你。目前你能回到的最老城市就是你自己。
        stk.push_back(u);// 住进客栈
        int child = 0;// 记录在 DFS 树中，u 有几个真正的“儿子”

        // 特判孤立点：自己单独构成一个 v-BCC，且不是割点
        if(p == 0 && adj[u].empty())
        {
            vbccnt++;// 记录找到一个全新的 v-BCC
            stk.pop_back();// 把这个孤立点从客栈(栈)里请出去
            vbc.push_back({u});//独立的vbc
            return;// 结束对这个点的探索
        }

        for(int v : adj[u])
        {
            if(!dfn[v])// 发现一座从未去过的新城市 v，说明 v 是 u 的儿子
            {
                child++;
                dfs(v, u);// 派人去探索 v

                // 探索完毕，v 把它的情报带回来了。
                // 如果 v 能用时光机回到更老的城市，那 u 借着 v 的光，也能回到那个城市。
                low[u] = min(low[u], low[v]);

                // 🚨 割点判定核心定理 🚨
                if(low[v] >= dfn[u])
                {
                    isCut[u] = 1;
                    vbccnt++;// 发现了一个新的 v-BCC 城市群！
                    vector<int> comp;//存储vbc
                    // 把客栈里属于这个群的城市全赶出来
                    while(1)
                    {
                        int x = stk.back();
                        stk.pop_back();
                        comp.push_back(x);
                        if(x == v)// 🚨 核心：只弹到 v 为止！绝对不弹 u！
                            break;
                    }
                    comp.push_back(u);//u自己也包含在点双里面。
                    vbc.push_back(comp);//加进去vbc
                }
            }
            else if(v != p)
            {
                // 如果 v 以前来过，而且 v 不是刚走过来的父亲 p。
                // 说明发现了一条“返祖边”！这是一条通往古老年代的秘密捷径！
                low[u] = min(low[u], dfn[v]);
            }
        }
        // 如果 u 是这次 DFS 的大本营（根节点），它没有父亲。
        // 如果它只有一个儿子，就算把它炸了，下面的儿子依然是一整块，不会分裂。
        // 所以根节点必须要有至少 2 个独立的儿子，才能当割点。
        if(p == 0 && child < 2)
            isCut[u] = 0;
    }

    void work()
    {
        for (int i = 1; i <= n;i++)
        {
            if(!dfn[i])// 因为图可能不连通，有多个国家，所以要循环检查，防止有城市没访问到
            {
                stk.clear();
                dfs(i);
            }
        }
        // 最后统计全图到底有几个割点
        for (int i = 1; i <= n;i++)
        {
            if(isCut[i])
                cutcnt++;
        }
    }
};