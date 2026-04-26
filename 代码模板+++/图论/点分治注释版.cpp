#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct PointDiv
{
    struct Edge
    {
        int to, weight;
    };

    int n, k;
    vector<vector<Edge>> adj;
    vector<int> siz, maxp, vis;// siz:子树大小; maxp:最大连通块大小; vis:是否被当做重心删除了
    int root, totalSize;// root:当前找到的重心; totalSize:当前连通块的总大小

    vector<int> queries;// 存储所有的 k
    vector<int> ans;// 存储每个询问的答案

    
    vector<int> judge;// judge: 核心记忆数组，judge[x]为1表示“目前已经找到了长度为x的半条路”
    vector<int> curDis;// curDis: 临时存放当前正在遍历的那个子分支里所有的距离
    vector<int> allDis;// allDis: 存放当前重心下，所有分支产生的距离，用来最后统一清空judge

    // 初始化
    PointDiv(int n_, const vector<int> &q, int MAXK) : n(n_), queries(q), k(MAXK)
    {
        adj.resize(n + 1);
        siz.resize(n + 1);
        maxp.resize(n + 1);
        vis.resize(n + 1);
        ans.resize(queries.size(), 0);

        //最大就是MAXK，我们开MAXK + 1
        judge.resize(MAXK + 1, 0);
    }

    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // 求树的重心
    void getRoot(int u, int p)
    {
        siz[u] = 1;
        maxp[u] = 0;
        for(const auto &e : adj[u])
        {
            int v = e.to;
            if(v == p || vis[v])
                continue;
            getRoot(v, u);
            siz[u] += siz[v];
            maxp[u] = max(maxp[u], siz[v]);
        }
        maxp[u] = max(maxp[u], totalSize - siz[u]);
        if(root == 0 || maxp[u] < maxp[root])
            root = u;
    }

    // 获取当前子树中所有点到重心的距离
    void getDist(int u, int p, int d)
    {
        //剪枝
        if(d > k)
            return;
        curDis.push_back(d);
        for(const auto &e : adj[u])
        {
            int v = e.to;
            int w = e.weight;
            if(v == p || vis[v])
                continue;
            getDist(v, u, d + w);
        }
    }

    // 核心逻辑：计算经过当前重心 root 的路径
    void calc(int u)
    {
        allDis.clear();
        judge[0] = 1;// 到重心自身的距离为 0

        // 依次处理重心的每一棵子树
        for(const auto &e : adj[u])
        {
            int v = e.to;
            int w = e.weight;

            if(vis[v])
                continue;

            curDis.clear();
            getDist(v, u, w);

            // 1. 结算答案：查询 {前面已遍历过的子树距离} + {当前子树距离} 是否等于 k
            for(int d : curDis)
            {
                for (int i = 0; i < queries.size(); i++)
                {
                    if(ans[i])
                        continue;
                    if(queries[i] >= d && judge[queries[i] - d])
                        ans[i] = 1;
                }
            }

            // 2. 将当前子树的距离加入 judge，供后面的子树匹配
            for(int d : curDis)
            {
                judge[d] = 1;
                allDis.push_back(d);
            }
        }

        // 3. 擦屁股：O(总节点数) 清空 judge 数组
        for(int d : allDis)
        {
            judge[d] = 0;
        }
    }

    void sol(int u)
    {
        vis[u] = 1;// 标记当前重心已经被砍掉
        calc(u);// 结算经过当前重心的答案

        // 递归处理子树
        for (const auto &e : adj[u])
        {
            int v = e.to;
            if(vis[v])
                continue;
            totalSize = siz[v];
            root = 0;
            getRoot(v, 0);// 找子树的重心
            sol(root);// 递归分治
        }
    }

    // 对外启动接口
    vector<int> run()
    {
        totalSize = n;
        root = 0;
        getRoot(1, 0);
        sol(root);
        return ans;
    }
};