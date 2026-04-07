// #include <bits/stdc++.h>
// using namespace std;
// int n, m;
// const int MAXN = 1600;
// const int MAXM = 5e4 + 5;
// const int INF = 0x3f3f3f3f;
// int dp[MAXN];
// int ind[MAXN];
// struct pp{
//     int to, w;
// };
// vector<pp> adj[MAXN];
// int main()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     cin >> n >> m;

//     for (int i = 1; i <= n;i++)
//     {
//         dp[i] = -INF;
//     }
//         for (int i = 1; i <= m; i++)
//         {
//             int id;
//             pp tp;
//             cin >> id >> tp.to >> tp.w;
//             ind[tp.to]++;
//             adj[id].push_back(tp);
//         }

//     queue<int> q;
//     for (int i = 1; i <= n;i++)
//     {
//         if(ind[i] == 0)
//             q.push(i);
//     }
//     dp[1] = 0;
//     while(!q.empty())
//     {
//         int u = q.front();
//         q.pop();
//         for(auto it : adj[u])
//         {
//             if(dp[u] != -INF)
//                 dp[it.to] = max(dp[it.to], dp[u] + it.w);
//             ind[it.to]--;
//             if(ind[it.to] == 0)
//                 q.push(it.to);
//         }
//     }
//     if(dp[n] == -INF)
//         cout << -1;
//     else
//         cout << dp[n];
// }

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1600;
const int MAXM = 5e4 + 5;
const int INF = 0x3f3f3f3f;
int dp[MAXN];// 备忘录：dp[u] 存储从 u 到 n 的最长路径长度
struct edge{
    int to, w;
};
int n, m;
vector<edge> adj[MAXN];
int vis[MAXN];// 记录该点是否已经计算过
int dfs(int u)
{
    if(u == n)// n 到 n 的距离自然是 0。这是递归停止的信号
        return dp[u] = 0;
    if(vis[u])//如果 vis[u] 是真，说明之前已经从这个点到达过终点，直接拿走 dp[u]，时间复杂度瞬间从指数级降到 O(1)。
        return dp[u];
    int res = -INF;
    for(auto it : adj[u])
    {
        int nextdis = dfs(it.to);// 递归询问：从邻居“去终点”最长多远？
        if(nextdis != -INF)// 如果邻居能走到终点
            res = max(res, nextdis + it.w);// 更新当前点的最长路
    }
    vis[u] = 1;
    return dp[u] = res;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);


    cin >> n >> m;
    int u, v, w;
    for (int i = 1; i <= m;i++)
    {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    int ans = dfs(1);
    //为什么用 ans <= -INF / 2 而不是 ans == -INF？因为路径中可能有负权边，-INF 加上一些权值后会稍微变大一点，所以用一个范围来判定更稳健。
    if(ans <= -INF / 2)
        cout << -1;
    else
        cout << ans;
}