#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct VirtualTree
{
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, dep;
    vector<vector<int>> st;//倍增求LCA
    int timer;//时间戳计数

    // vtadj 就是压缩后的虚树！
    // 极其重要：每次只清空 vtnodes 里面的节点，绝不能用 memset，否则退化为 O(N)
    vector<vector<int>> vtadj;
    vector<int> vtnodes;

    VirtualTree(int n_) : n(n_)
    {
        adj.resize(n + 1);
        vtadj.resize(n + 1);
        dfn.resize(n + 1, 0);
        dep.resize(n + 1, 0);
        st.assign(20, vector<int>(n + 1, 0));
        timer = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 预处理 DFN 序、深度、以及倍增求 LCA 的 ST 表
    void dfs(int u, int p, int d)
    {
        dfn[u] = ++timer;
        dep[u] = d;
        st[0][u] = p;
        for (int i = 1; i < 20;i++)
            st[i][u] = st[i - 1][st[i - 1][u]];
        for(int v : adj[u])
        {
            if(v != p)
                dfs(v, u, d + 1);
        }
    }

    void init(int root = 1)
    {
        dfs(root, 0, 1);
    }

    // 倍增求 LCA
    int getLCA(int u, int v)
    {
        if(dep[u] < dep[v])
            swap(u, v);
        for (int i = 19; i >= 0; i--)
        {
            if(dep[st[i][u]] >= dep[v])
                u = st[i][u];
        }

        if(u == v)
            return u;

        for (int i = 19; i >= 0;i--)
        {
            if(st[i][u] != st[i][v])
            {
                u = st[i][u];
                v = st[i][v];
            }
        }
        return st[0][u];
    }

    // 🌟 核心：一键构建虚树，返回虚树的根节点
    int build(vector<int> nodes)
    {
        if(nodes.empty())
            return 0;

        // 1. 按照 DFN 序把散落的点排好
        sort(nodes.begin(), nodes.end(), [&](int u, int v)
             { return dfn[u] < dfn[v]; });

        // 2. 把相邻节点的 LCA 全部加进去，这就是虚树所需的全部转折点
        int k = nodes.size();
        for (int i = 0; i < k - 1;i++)
            nodes.push_back(getLCA(nodes[i], nodes[i + 1]));

        // 3. 再次排序，并去重
        sort(nodes.begin(), nodes.end(), [&](int u, int v)
             { return dfn[u] < dfn[v]; });

        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        // 4. 连边构建虚树！排序后，相邻元素的 LCA 就是它们在虚树上的父节点
        vtnodes = nodes;// 备份一下，等会儿清空 vtadj 时只清空这里面的点，效率 O(k)
        for (int i = 1; i < nodes.size();i++)
        {
            // 拿到 DFN 序相邻的两个点 u = nodes[i-1], v = nodes[i]
            // 算出它们的最近公共祖先 p
            int p = getLCA(nodes[i - 1], nodes[i]);
            // 重点：在虚树中，p 是 v 的父亲，直接连边
            // 注意：这里连的是有向边 (p -> v)，因为虚树通常当做有根树处理
            //为什么，因为我们的根已经确定是nodes[0]了，我们在遍历的时候只需要一直向下去找就好了
            //也可以建双向边，不过在写dfs的时候还要加上特判，以及会有时间损耗。
            vtadj[p].push_back(nodes[i]);
        }

        return nodes[0];// 第一个点绝对是深度最浅的，即虚树的根
    }

    // 每次查询完，必须调用此函数光速清空虚树，迎接下一次查询
    void clear()
    {
        for(int u : vtnodes)
            vtadj[u].clear();
        vtnodes.clear();
    }
};