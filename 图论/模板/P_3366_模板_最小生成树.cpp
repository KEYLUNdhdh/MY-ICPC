#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e3 + 5;
const int MAXM = 2e5 + 5;
const int INF = 1e9;
//链式前向星
struct edge {
    int v;// 这条边的终点去哪？ (Destination)
    int w;// 这条边有多长？ (Weight)
    int next = 0;// 同一个起点的“上一条边”在哪？ (Linked List)
} e[MAXM << 1];// 无向图，边数要开 2 倍

int head[MAXN];// head[u] 表示：以 u 为起点的“最后加入的那条边”在数组 e 中的下标。
int cnt;// 给边编号的计数器。
int dis[MAXN];// 它代表 点 i 距离“最小生成树”这个集合的最短距离。
int vis[MAXN];// 标记数组：vis[i]=true 表示点 i 已经在生成树中
int n, m, tot, ans;// tot记录已加入生成树的点数

//head[u] 永远存的是最新那条边的位置。
//e[i].next 顺藤摸瓜找到之前的边。
inline void add(int u,int v,int w)
{
    e[++cnt].v = v;// 1. 申请一个新的边位置 cnt，记录终点是 v
    e[cnt].w = w;// 2. 记录权值是 w
    // 下面这两步是“插头法”链接：
    e[cnt].next = head[u];// 3. 新边的 next 指向 u 节点原本的第一条边
    head[u] = cnt;// 4. 更新 u 节点的第一条边为当前这条新边
}
//Prim 算法是一种贪心算法，它的逻辑类似于“长树”。任选一个点作为起点（通常选 1 号点），放入集合 A（代表最小生成树的节点集合）。
//维护一个数组 dis，表示未进入集合的点到集合 A 中任意点的最短距离。每次循环从未进集合的点中，选出 dis 值最小的那个点，将其加入集合 A。
//利用这个新加入的点，去更新它邻接点的 dis 值。重复直到所有点都在集合中。
//时间复杂度O(N^2)，适用于稠密图(M约等于N^2
inline int prim()
{
    // --- 1. 初始化 ---
    // 刚开始，除了起点，所有人都离树无穷远
    for (int i = 2; i <= n;i++)
    {
        dis[i] = INF;
    }
    // --- 2. 起点入队前奏 ---
    // 假设 1 号点是树的根。先看看 1 号点周围的人，更新他们的距离。
    // i = head[1] 开始，顺着 next 遍历所有从 1 出发的边
    for (int i = head[1]; i;i = e[i].next)
    {
        dis[e[i].v] = min(dis[e[i].v], e[i].w);
    }

    int now = 1;// now 表示最新加入树的那个点
    vis[1] = 1;// 1号点已入伙
    tot = 1;// 目前树里有 1 个点

    // --- 3. 循环建树 ---
    // 只要树里的点还没到 n 个，就继续找
    while(tot < n)
    {
        int minn = INF;
        now = 0;// 用来存这一轮找到的“最近的那个点”
        // [核心步骤 A]：在所有“流浪”的点中，找一个离树最近的
        for (int i = 2; i <= n;i++)
        {
            // 如果 i 没入伙，且距离树的距离比当前记录的最小还小
            if(!vis[i] && dis[i] < minn)
            {
                minn = dis[i];// 更新最小距离
                now = i;// 记下这个点
            }
        }
        // 如果转了一圈，发现 minn 还是 INF，说明剩下的点和树完全断开了
        if(minn == INF)
        {
            cout << "orz";
            return -1;
        }
        // [核心步骤 B]：,如果找到了，把找到的这个点拉入伙
        ans += minn;
        vis[now] = 1;
        tot++;
        // [核心步骤 C]：更新邻居 (打折时间)
        // 既然 now 加入了树，那么 now 的邻居们，离树的距离可能会变近！
        for (int i = head[now]; i;i = e[i].next)
        {
            int v = e[i].v;
            if (!vis[v] &&e[i].w < dis[v])
            {
                dis[v] = e[i].w;
            }
        }
    }

    cout << ans;
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    prim();
}