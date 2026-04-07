#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e3 + 5;
const int MAXM = 2e5 + 5;
struct edge{
    int u;
    int v;
    int w;
} e[MAXM];
//Kruskal 算法基于边的贪心。将所有边按权值从小到大排序。
//依次枚举每一条边 (u, v)。利用并查集判断 u 和 v 是否已经连通（即是否在同一棵树内）。
//若不在同一集合：选取这条边，将 u, v 所在的集合合并，答案加上边权。
//若已在同一集合：跳过这条边（否则会形成环）。当选取的边数达到 N-1 条时，算法结束。
//适用场景：稀疏图（点多边少）。O(Mlog M)
struct DSU
{
    vector<int> f, siz;
    DSU() {};
    DSU(int n)
    {
        init(n);
    }
    //input n,open n + 1
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }
    int find(int x)
    {
        while(x != f[x])
            x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(siz[x] < siz[y])
            swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};

int n, m, ans, cnt;
inline bool cmp(edge e1,edge e2)
{
    return e1.w < e2.w;
}
inline void kruskal()
{
    cin >> n >> m;
    DSU ds(n);
    for (int i = 0; i < m; i++)
    {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    // 1. 排序,因为要从小到大慢慢去筛
    sort(e, e + m, cmp);
    // 2. 遍历所有边
    for (int i = 0; i < m;i++)
    {
        int eu = ds.find(e[i].u);// 找 u 的祖先
        int ev = ds.find(e[i].v);// 找 v 的祖先
        // 3. 判断是否连通
        if(eu == ev)
            continue;// 已经在同一个连通块，跳过，防止成环
        // 4. 合并与统计
        ans += e[i].w;// 累加边权
        ds.merge(eu, ev); // 合并两个集合
        // 如果选够了 n-1 条边，说明最小生成树已建成
        if(++cnt == n - 1)
            break;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    kruskal();
    // 判断连通性
    // 如果选出来的边数小于 n-1，说明图不连通
    if(cnt == n - 1)
    {
        cout << ans;
    }
    else
    {
        cout << "orz";
    }

    return 0;
}
