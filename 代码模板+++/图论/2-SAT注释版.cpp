#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SCC
{
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;

    SCC() {}
    SCC(int n_)
    {
        init(n_);
    }
    //1 - index
    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.resize(n + 1);
        bel.assign(n + 1, 0);
        stk.clear();
        cur = cnt = 1;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void dfs(int x)
    {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for(auto y : adj[x])
        {
            if(!dfn[y])
            {
                dfs(y);
                low[x] = min(low[x], low[y]);
            }
            else if(!bel[y])
            {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if(dfn[x] == low[x])
        {
            int y;
            do{
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }

    vector<int> work()
    {
        for (int i = 1;i <= n;i++)
        {
            if(!dfn[i])
                dfs(i);
        }
        return bel;
    }
};

struct TwoSAT
{
    int n;
    SCC scc;// 内部持有一个 SCC 实例
    vector<int> ans;// 存储最终的布尔赋值

    TwoSAT() {}
    TwoSAT(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        // 共有 2n 个节点，交给 SCC 初始化
        // 1 ~ n 表示 false，n+1 ~ 2n 表示 true
        scc.init(2 * n);
        ans.assign(n + 1, 0);
    }

    // 神级辅助函数：直接根据变量和期望的布尔状态，返回对应的图中节点编号
    // state 为 false(0) 返回 u，state 为 true(1) 返回 u + n
    int getNode(int u, bool state)
    {
        return u + state * n;
    }

    // 添加约束：u 的状态为 fu，或者 v 的状态为 fv
    void addClause(int u, bool fu, int v, bool fv)
    {

        // 逻辑推导 1：如果 u 不满足 fu (即 u 是 !fu)，那么 v 必须满足 fv
        scc.addEdge(getNode(u, !fu), getNode(v, fv));

        // 逻辑推导 2：如果 v 不满足 fv (即 v 是 !fv)，那么 u 必须满足 fu
        scc.addEdge(getNode(v, !fv), getNode(u, fu));
    }

    // 求解并得出方案
    bool sol()
    {
        scc.work();

        for (int i = 1; i <= n;i++)
        {
            // 同一个变量的 true 节点和 false 节点在同一个 SCC 里，无解
            if(scc.bel[getNode(i, false)] == scc.bel[getNode(i, true)])
                return false;

            // 拓扑序贪心：bel 编号越小，拓扑序越靠后，越安全
            ans[i] = scc.bel[getNode(i, true)] < scc.bel[getNode(i, false)];
        }
        return true;
    }
};