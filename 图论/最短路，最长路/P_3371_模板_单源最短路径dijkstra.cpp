//Dijkstra 是一种贪心算法。
//对于 n 个点，将其分成两个部分。一部分中的点都已经找到了最短路径的长度，另一部分未找到。 
//将 dis 值最小的那个点确定为已找到最短路径（贪心核心）
//它只能处理非负权边，因为如果出现负权边，此时贪心算法就失效了。即经过其他点再绕回 u 的路径，长度不再一定会大于或等于当前路径。
//时间复杂度O(MlogM)//M为边的个数
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5 + 5;
const int INF = 2147483647;
struct edge{
    int to, w;// 终点和边权
};
struct node{
    int id,dis;// 节点编号和当前到起点的距离
    // 优先队列排序规则：距离越小越靠前
    bool operator>(const node &b) const
    {
        return dis > b.dis;
    }
};
vector<edge> adj[MAXN];// 邻接表，存每个点的出边
int dis[MAXN];// 存储起点到每个点的最短距离
int n, m, s;
void dij(int start)
{
    for (int i = 1; i <= n;i++)
        dis[i] = INF;// 1. 初始化所有点距离为无穷大 
    dis[start] = 0;// 2. 起点到自己的距离为 0

    priority_queue<node, vector<node>, greater<node>> pq;
    pq.push({start, 0});// 3. 将起点放入优先队列
    while(!pq.empty())
    {
        node curr = pq.top();// 1. 取出当前距离最短的点
        //这样取出路程最短的点可以保证我们这时候首次处理完这个点时已经保证这个点是最短路，后续只要做这个点的冗余检查就行。这是贪心的精髓所在，
        pq.pop();

        int u = curr.id;
        int d = curr.dis;
        // 2. 懒惰删除/冗余检查
        //同一个点 u 可能会多次进入优先队列。当我们从堆顶取出 u 时，如果它当时的距离 d 已经比我们记录的 dis[u] 还要大了，说明它是一个“过时的旧数据”，直接跳过即可。
        //这个保证了只有当 u 第一次以“历史最短”的身份出堆时，也就是找到了到达u的最短路时，它的边才会被松弛。
        //所以每条边最多只会被松弛一次
        if(d > dis[u])
            continue;
        // 3. 遍历 u 的所有邻居
        for(auto &e : adj[u])
        {
            // 如果 经过 u 到达 e.to 的路径比之前的记录更短
            if(dis[u] + e.w < dis[e.to])
            {
                dis[e.to] = dis[u] + e.w;// 更新最短距离（松弛）    
                pq.push({e.to, dis[e.to]});// 将更新后的点再次入队，因为这个点的更改会进一步影响其他点//入队后本质上说明这个点已经找到最短路了，我们去寻找它所影响的点
            }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> s;
    for (int i = 0; i < m;i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    dij(s);

    for (int i = 1; i <= n;i++)
    {
        cout << dis[i] << " ";
    }
}