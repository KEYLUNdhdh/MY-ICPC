#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct DSUonTree
{
    int n;
    vector<vector<int>> adj;
    vector<int> color;
    vector<int> sz, son;

    // ===== 核心状态变量 =====
    vector<int> cnt;// cnt[c] 表示当前统计区间内，颜色 c 出现的次数 
    int maxcnt;// 当前出现的最多次数
    i64 sumcolor;// 出现次数等于 max_cnt 的颜色编号之和
    vector<i64> ans;// 记录每个节点的最终答案
    int skip;// 核心剪枝标记：用于在统计轻儿子时，跳过重儿子

    DSUonTree(int n_, const vector<int> &c) : n(n_), color(c)
    {
        adj.resize(n + 1);
        sz.resize(n + 1, 0);
        son.resize(n + 1, 0);

        // 假设颜色编号最大为 n，如果颜色值域更大，需要离散化
        cnt.resize(n + 1, 0);
        ans.resize(n + 1, 0);
        maxcnt = 0;
        sumcolor = 0;
        skip = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 步骤一：预处理，找出每个节点的子树大小(sz)和重儿子(son)
    void dfsSz(int u, int p)
    {
        sz[u] = 1;
        int maxsub = 0;
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            dfsSz(v, u);
            sz[u] += sz[v];
            if(sz[v] > maxsub)
            {
                maxsub = sz[v];
                son[u] = v;
            }
        }
    }

    // 暴力统计函数：val=1表示添加，val=-1表示清除
    void add(int u, int p, int val)
    {
        int c = color[u];
        cnt[c] += val;

        // 只有在添加时才需要动态维护最大值和答案
        // 清除时我们直接在外部粗暴归零即可
        if(val == 1)
        {
            if(cnt[c] > maxcnt)
            {
                maxcnt = cnt[c];
                sumcolor = c;// 出现新的最大次数，直接覆盖答案
            }
            else if(cnt[c] == maxcnt)
            {
                sumcolor += c;// 次数持平，累加颜色编号
            }
        }

        for(int v : adj[u])
        {
            // 🌟 灵魂剪枝：绝对不要重复遍历 skip 节点（通常是重儿子）
            if(v == p || v == skip)
                continue;
            add(v, u, val);
        }
    }

    // 步骤二：核心启发式合并过程
    void dfsDSU(int u, int p, bool keep)
    {
        // 1. 先递归处理所有【轻儿子】，并【不保留】它们的统计信息
        for(int v : adj[u])
        {
            if(v == p || v == son[u])
                continue;
            dfsDSU(v, u, false);
        }

        // 2. 最后递归处理【重儿子】，并【保留】它的统计信息
        if(son[u])
        {
            dfsDSU(son[u], u, true);
            skip = son[u];// 标记重儿子，等会儿加上轻儿子时不要再重复遍历它了！
        }

        // 3. 把当前节点本身，以及它的所有【轻儿子】的子树信息加上去
        //避免重儿子的节点被加两次
        // 因为 skip 已经被设置为了 son[u]，所以 add 函数会自动跳过重儿子
        add(u, p, 1);
        skip = 0;// 用完必须立刻重置，千万别影响后续！

        // 4. 此时 cnt 数组里完美包含了 u 整个子树的信息，记录答案！
        ans[u] = sumcolor;

        // 5. 如果当前节点 u 本身是它父亲的轻儿子，那就必须【清除】刚才加上的所有信息
        if(!keep)
        {
            add(u, p, -1);
            maxcnt = 0;
            sumcolor = 0;
        }
    }

    vector<i64> run(int root = 1)
    {
        dfsSz(root, 0);
        dfsDSU(root, 0, true);// 根节点的数据最后不用清除
        return ans;
    }
};