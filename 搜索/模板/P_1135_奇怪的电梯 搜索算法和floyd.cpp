#include <bits/stdc++.h>
using namespace std;
int n, a, b;
//O(n**3)n较少时可以用
void floyd()
{
    int floyd1[205][205];
    memset(floyd1, 0x3f, sizeof(floyd1));//0x3f是设置一个非常大的值
    cin >> n >> a >> b;
    for (int i = 1; i <= n;i++)
        floyd1[i][i] = 0;//自己到自己楼层不用按按钮：
    for (int i = 1,tp; i <= n;i++)
    {
        cin >> tp;
        //第i楼能到达i- tp 或 i+ tp，前提是在范围内
        if (i - tp >= 1)
        {
            floyd1[i][i - tp] = min(floyd1[i][i - tp], 1);//本质是构建长为1的边
        }
        if (i + tp <= n)
        {
            floyd1[i][i + tp] = min(floyd1[i][i + tp], 1);
        }
    }
    for (int k = 1; k <= n;k++)
        for (int i = 1; i <= n;i++)
            for (int j = 1; j <= n;j++)
            {
                floyd1[i][j] = min(floyd1[i][j], floyd1[i][k] + floyd1[k][j]);
            }
    cout << (floyd1[a][b] == 0x3f3f3f3f ? -1 : floyd1[a][b]);
}
//BFS 就像水波扩散一样，一层一层地搜索。

// 第 0 层：起点 A。

// 第 1 层：从 A 按一次按钮能到的楼层。

// 第 2 层：从第 1 层楼层按一次按钮能到的楼层。

// ...
// 因为它是按层级扩展的，所以第一次搜索到终点 B 时，经过的层数一定是最少的按键次数。
void bfs()
{
    queue<int> q;
    int k[205] = {0};//存储每个楼层的移动层数
    int vis[205] = {0};//用于判断楼层是否到达过，避免重复到达陷入死循环
    int dis[205];//记录操作次数
    memset(dis, -1, sizeof(dis));//没到的地方初始化为-1
    cin >> n >> a >> b;
    for (int i = 1; i <= n;i++)
        cin >> k[i];
    // 起点入队
    q.push(a);
    vis[a] = 1;
    dis[a] = 0;
    while(!q.empty())
    {
        int u = q.front();//取出队首楼层
        q.pop();
        if (u == b)
        {
            cout << dis[u];
            return;
        }
        int up = u + k[u];
        int down = u - k[u];
        //向上
        if (up <= n && !vis[up])
        {
            vis[up] = true;
            dis[up] = dis[u] + 1;
            q.push(up);
        }
        //向下
        if (down >= 1 && !vis[down])
        {
            vis[down] = true;
            dis[down] = dis[u] + 1;
            q.push(down);
        }
    }
    // 如果出循环说明empty，输出-1;
    cout << -1;
    return;
}
// DFS 就像走迷宫，一条路走到黑，撞了南墙再回头。

// 它可能会先绕一个大圈子到达 B，然后再回溯尝试别的路。

// 所以，DFS 第一次到达 B 时，算出来的步数不一定是最优的。我们需要遍历所有可能的路径，取最小值。

// 关键点与剪枝（Pruning）：
// 普通的 DFS 会因为有环（比如 3楼->5楼->3楼）而死循环。
// 为了求最短路，我们需要一个最优性剪枝策略：

// 使用一个数组 min_steps[i] 记录到达第 i 层目前找到的最少步数。

// 当我们再次来到第 i 层时，如果当前的步数 step 已经比 min_steps[i] 大了（或者相等），说明现在的走法不如之前的走法好，直接剪枝（return），不再继续往下搜。
    int k[205] = {0};//存储每个楼层的移动层数
    int ans = 0x3f3f3f3f;//初始化答案无限大
    int min1[205] = {0};//记录到一个楼层最短操作次数
void dfs(int cur,int step)//cur当前楼层,step当前已走步数
{
    //剪枝
    //越界
    if (cur < 1 || cur > n)
        return;
    //已经到达过
    if (step >= min1[cur])
        return;
    //以上都不满足，更新 
    min1[cur] = step;
    if (cur == b)
    {
        ans = min(ans, step);
        // 其实可以写成，ans = step;，因为已经满足step这里是历史最优
        // 即使在这个特定代码里能行，我依然强烈建议你写 ans = min(ans, steps)，原因有二：

        // 代码健壮性：如果你稍微调整一下代码顺序（例如把剪枝放在判断终点之后），或者把剪枝条件改得宽松一点（例如只判断环，不判断最优性），那么 ans = steps 就会导致严重的 Bug。

        // 语义清晰：ans 的定义是“最小步数”。写 ans = min(...) 能够清晰地告诉阅读代码的人（以及未来的你自己）：“我在尝试更新最小值”。而写 ans = steps 会让人误以为只要到了终点就是答案。
        return;
    }
    dfs(cur + k[cur], step + 1);
    dfs(cur - k[cur], step + 1);
}
void dfssolve()
{
    cin >> n >> a >> b;
    for (int i = 1; i <= n;i++)
        cin >> k[i];
    memset(min1, 0x3f, sizeof(min1));
    dfs(a, 0);
    cout << (ans == 0x3f3f3f3f ? -1 : ans);
}
int main()
{
    // floyd();
    // bfs();
    dfssolve();
    return 0;
}