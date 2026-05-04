#include  <bits/stdc++.h>
using namespace std;
using i64 = long long;
//P4556 【模板】线段树合并 / [Vani 有约会] 雨天的尾巴

constexpr int MAXZ = 1e5 + 5;
// 因为题目要求统计“哪种米最多”，我们不能只存总数，必须为每个房子建一棵线段树，下标代表“大米的种类”。
struct dynamicSegmentTree
{
    int tot;// 节点池计时器（发号器），每次 ++tot 就会诞生一个新节点
    // 注意：这里的 ls 和 rs 存的不是传统的 2*p 和 2*p+1！
    // 它们存的是左儿子和右儿子在这个 vector 里面的“真实下标(tot)”！
    vector<int> ls, rs, maxx, maxId;

    dynamicSegmentTree(int maxNodes):tot(0), ls(maxNodes, 0), rs(maxNodes, 0), maxx(maxNodes, 0), maxId(maxNodes, 0) {}

    void pull(int p)
    {
        if(maxx[ls[p]] >= maxx[rs[p]])
        {
            maxx[p] = maxx[ls[p]];
            maxId[p] = maxId[ls[p]];
        }
        else
        {
            maxx[p] = maxx[rs[p]];
            maxId[p] = maxId[rs[p]];
        }
    }

    void update(int &p, int l, int r, int pos, int val)
    {
        // 🚨 核心语法：int &p 是引用传递！
        // 如果当前节点不存在 (!p)，现捏一个 (++tot)。
        // 因为是引用，所以其父节点的 ls 或 rs 会被直接修改为这个新的 tot！
        if(!p)
            p = ++tot;
        if(l == r)// 到了叶子节点（具体的某一种大米）
        {
            maxx[p] += val;// 大米数量增加（或减少）
            maxId[p] = (maxx[p] > 0) ? l : 0;
            return;
        }
        int m = l + r >> 1;
        // 只需要往包含 pos 的那一半走，另一半连内存都不用开
        if (pos <= m)
            update(ls[p], l, m, pos, val);
        else
            update(rs[p], m + 1, r, pos, val);
        pull(p);// 走完别忘了更新老父亲的信息
    }
    // 返回值是合并后的新树根
    int merge(int p, int q, int l, int r)
    {
        // 如果父亲这块区间是空的，直接把儿子的整块区间“嫁接”过来
        // 如果儿子是空的，直接保留父亲的。极其省时！
        if(!p || !q)
            return p | q;
        if(l == r)// 到了叶子节点
        {
            maxx[p] += maxx[q];
            maxId[p] = (maxx[p] > 0) ? l : 0;
            return p;
        }

        int m = l + r >> 1;
        // 递归合并左半边，并将合并后的新左儿子挂在父亲的 ls[p] 上
        ls[p] = merge(ls[p], ls[q], l, m);
        // 递归合并右半边
        rs[p] = merge(rs[p], rs[q], m + 1, r);
        pull(p);// 更新父亲的最大值
        return p;// 返回合并后的爹
    }  
};

struct HLD 
{
    int n, root;
    vector<vector<int>> adj;
    vector<int> sz, dep, fa, son, top;

    HLD(int n_, int r_) : n(n_), root(r_), adj(n_ + 1), sz(n_ + 1, 0), dep(n_ + 1, 0), fa(n_ + 1, 0), son(n_ + 1, 0), top(n_ + 1, 0) {}

    void addEdge(int u, int v) 
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs1(int u, int p, int d) 
    {
        dep[u] = d;
        fa[u] = p;
        sz[u] = 1;
        int max_sz = -1;
        for (int v : adj[u]) 
        {
            if (v == p) continue;
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > max_sz) 
            {
                max_sz = sz[v];
                son[u] = v;
            }
        }
    }

    void dfs2(int u, int t) 
    {
        top[u] = t;
        if (!son[u]) return;
        dfs2(son[u], t);
        for (int v : adj[u]) 
        {
            if (v != fa[u] && v != son[u])
                dfs2(v, v);
        }
    }

    void init() 
    {
        dfs1(root, 0, 1);
        dfs2(root, root);
    }

    int getLCA(int u, int v) 
    {
        while (top[u] != top[v]) 
        {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};