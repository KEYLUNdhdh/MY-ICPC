// #include <bits/stdc++.h>
// #define int long long
// using namespace std;
// int n;
// struct po{
//     int w, u, v;
// } a[200];
// int flo[200][200];
// signed main()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     cin >> n;
//     int x, y, z;
//     for (int i = 1; i <= n;i++)
//     {
//         cin >> a[i].w >> a[i].u >> a[i].v;
//     }
//     memset(flo, 0x3f3f3f3f, sizeof(flo));
//     for (int i = 1; i <= n;i++)
//     {
//         flo[i][i] = 0;
//     }
//     for (int i = 0; i <= n;i++)
//     {
//         flo[i][a[i].u] = 1;
//         flo[i][a[i].v] = 1;
//         flo[a[i].u][i] = 1;
//         flo[a[i].v][i] = 1;
//     }
//     for (int k = 1; k <= n;k++)
//         for (int i = 1; i <= n;i++)
//             for (int j = 1; j <= n;j++)
//             {
//                 flo[i][j] = min(flo[i][j], flo[i][k] + flo[k][j]);
//             }
//     int minn = 0x3f3f3f3f;
//     for (int i = 1; i <= n;i++)
//     {
//         int res = 0;
//         for (int j = 1; j <= n;j++)
//         {
//             res += flo[i][j] * a[j].w;
//         }
//         minn = min(minn, res);
//     }
//     cout << minn;
// }

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e3;
//head[maxn]：存每个节点的第一条边的索引。
//tot：边的计数器。
//n：节点总数。
//deep[maxn]：每个节点的深度（根节点为 1）。
//sz[maxn]：节点本身的居民数（题目输入的 $w$）。
//pre[maxn]：子树总人数（包含节点自己 + 所有子孙）。
//ans：最终答案（最小距离和）。
//dis[maxn]：当医院建在节点 $i$ 时，全树的总路程和。
int head[MAXN], tot, n, deep[MAXN], sz[MAXN], pre[MAXN], dis[MAXN],ans;
struct edge{
    int to, next;//to这条边通向哪一个点。//next：同起点的下一条边的索引
} e[MAXN << 1];
//add：这是向图中添加一条从 u 指向 v 的边的标准写法。
inline void add(int u,int v)
{
    e[++tot].to = v;//记录这条边去往 v。
    e[tot].next = head[u];//新边的下一条边，指向原本 u 的第一条边（头插法）。
    head[u] = tot;//更新 u 的第一条边为当前这条新边。
}
//rt 是当前节点（root），fa 是当前节点的父亲（father）。
inline void dfs(int rt,int fa)
{
    deep[rt] = deep[fa] + 1;//当前节点的深度 = 父亲深度 + 1。
    for (int i = head[rt]; i;i = e[i].next)
    {
        if(e[i].to == fa)//防止“儿子又走回父亲”导致死循环
            continue;
        dfs(e[i].to, rt);//递归处理子节点。
        pre[rt] += pre[e[i].to];//回溯时的关键操作。当前的子树总人数 += 某个子节点的子树总人数。
    }
}

inline void dp(int rt,int fa)
{
    for (int i = head[rt]; i; i = e[i].next)
    {
        if(e[i].to == fa)
            continue;
        //除了子节点那支以外的所有人 (pre[1] - pre[子])，距离都 +1。
        //子节点那支的所有人 pre[子]，距离都 -1。
        //+ (pre[1] - pre[子]) - pre[子]
        dis[e[i].to] = dis[rt] + pre[1] -  pre[e[i].to] * 2;
        if(dis[e[i].to] < ans)
            ans = dis[e[i].to];
        //递归：继续往下传，算出孙子节点的 dis
        dp(e[i].to, rt);
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n;i++)
    {
        int a, b;
        cin >> sz[i] >> a >> b;
        pre[i] = sz[i];// 初始化：子树人数至少包含自己的人口
        if(a)
        {
            add(i, a);
            add(a, i);
        }
        if(b)
        {
            add(i, b);
            add(b, i);
        }
    }
    deep[0] = 0;// 虚拟节点深度为0
    dfs(1, 0);// 从 1 号节点开始 DFS，算出 deep 和 pre 数组
    // --- 3. 暴力计算基准值 ---
    // 先算出医院建在 1 号节点时的总路程，作为 DP 的起点
    for (int i = 1; i <= n;i++)
    {
        // 某节点的路程贡献 = (该节点深度 - 1) * 该节点人数
        // 减1是因为根节点深度1
        dis[1] += (deep[i] - 1) * sz[i];
    }
    ans = dis[1];
    dp(1, 0);

    cout << ans;

    return 0;
}