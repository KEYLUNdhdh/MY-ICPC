//不能使用并查集，因为它只能处理无向图
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];// 反向邻接表
int ans[MAXN];// 存储每个点的 A(v)
int n, m;
//标记最大值：对于点 i，如果它还没有被标记过，就从它开始进行 DFS。在这个 DFS 过程中能访问到的所有点，它们能到达的最大编号一定就是 i（因为我们是从大到小遍历的）。
// 从当前点 v 开始，标记所有能反向到达的点
void dfs(int v,int maxid)
{
    ans[v] = maxid;// 标记该点能到达的最大编号
    for(auto it : adj[v])
    {
        if(ans[it] == 0)// 如果没被更大编号的点访问过
            dfs(it, maxid);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        // 核心：反向建边。原来 u -> v，现在存 v -> u
        adj[v].push_back(u);
    }
    // 从最大的点开始找
    for (int i = n; i >= 1;i--)
    {
        if(ans[i] == 0)
        {
            dfs(i, i);// 如果点 i 还没被标记过最大值
        }
    }
    for (int i = 1; i <= n;i++)
    cout << ans[i] << " ";
}