#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<int, int> pii;
struct EBCC
{
    int n;
    vector<vector<pii>> adj;
    vector<int> dfn, low, stk;
    // dfn[u]：时间戳。搜救队是第几个到达城市 u 的？
    // low[u]：时光机。从城市 u 出发，不走回头路，能找到一条暗道“穿越”回到的最古老城市的时间戳。
    // stk：历史客栈（栈）。把一路走来的城市先暂存起来，凑够一个“安全城市群（e-BCC）”就一波带走。
    int dfncnt, ebccnt, bridgecnt;
    vector<vector<int>> ebc;// 用来存储具体的边双连通分量
    EBCC(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<pii>());
        dfn.assign(n + 1, 0);// 0 表示没去过
        low.resize(n + 1, 0);
        stk.clear();
        dfncnt = ebccnt = bridgecnt = 0;
    }

    // 很多初学者通过判断 v != parent 来防止走回头路。但在高级竞赛中，图中可能有重边（两个城市之间修了两条不同的高速公路）。
    // 如果你判断 v != parent，合法的第二条路也会被屏蔽！用边的唯一 id 判重，才是工业级和 ACM 竞赛中最严谨的无敌写法！
    void addEdge(int u, int v, int id)
    {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    void dfs(int u, int inEdge = 0)// inEdge 记录我们是从哪条边走进 u 的
    {
        dfn[u] = low[u] = ++dfncnt;// 刚到这，发时间戳。最老只能回到自己。
        stk.push_back(u);// 住进客栈

        for(auto &[v, id] : adj[u])
        {
            if(!dfn[v])// 情况 A：发现一座没去过的新城市 v
            {
                dfs(v, id);// 派人顺着 id 这条路去探索 v

                // 探索完回来了。如果 v 找到了通往远古的暗道，u 借着 v 的光也能回去
                low[u] = min(low[u], low[v]);

                // 🚨 割边判定核心定理 🚨
                if(low[v] > dfn[u])
                    bridgecnt++;
            }
            else if(id != inEdge)// 情况 B：v 去过了，而且不是我们刚走过来的那条路！
            {
                // 恭喜！发现了一条“返祖边”（暗道）！形成环了！
                low[u] = min(low[u], dfn[v]);// 直接借用 v 的时间戳更新 u 的时光机
            }
        }

        // 所有的邻居都探索完了，结算时间！
        if(low[u] == dfn[u])
        {
            ebccnt++;// 发现了一个新的安全城市群！
            vector<int> comp; // 准备一个小袋子
            while(1)
            {
                int x = stk.back();// 把客栈最上面的人赶出来
                comp.push_back(x); // 弹出来的人无脑装进袋子
                stk.pop_back();
                if(x == u)// 直到把 u 自己也赶出来为止
                    break;
            }
            ebc.push_back(comp); // 把小袋子放进大袋子里
        }
    }

    void work()
    {
        for (int i = 1; i <= n;i++)// 图可能是不连通的（有多个国家），必须遍历每一个点
        {
            if(!dfn[i])
            {
                stk.clear();
                dfs(i);
            }
        }
    }
};

