//dfs不剪枝的情况下为全排列，O(n!)会T
// // 这样剪枝依旧会T
// #include <bits/stdc++.h>
// #define ld long double
// #define pii pair<ld,ld>
// using namespace std;
// int n;
// ld dis[20][20];
// int vis[25];
// // vector<ld> vec;
// ld sum = 0;
// ld minn = 1e9;
// ld distance(pii p1,pii p2)
// {
//     ld ans = (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
//     ans = pow(ans, 0.5);
//     return ans;
// }
// pii a[20];
// void dfs(int point,ld curdis,int cnt)
// {
//     if(curdis >= minn)
//         return;
//     if(cnt == n)
//     {
//         minn = min(minn, curdis);
//         return;
//     }
//     for (int j = 0; j <= n;j++)
//     {
//         if(j == point)
//             continue;
//         if(!vis[j])
//         {
//             // vec.push_back(dis[point][j]);
//             vis[j] = 1;
//             dfs(j,curdis + dis[point][j],cnt + 1);
//             // vec.pop_back();
//             vis[j] = 0;
//         }
//     }
// }
// int main()
// {
//     cin >> n;
//     a[0] = pii(make_pair(0, 0));
//     for (int i = 1; i <= n;i++)
//     {
//         cin >> a[i].first >> a[i].second;
//     }
//     for (int i = 0; i <= n;i++)
//     {
//         for (int j = 0; j <= n;j++)
//         {
//             dis[i][j] = distance(a[i], a[j]);
//         }
//     }
//     vis[0] = 1;
//     dfs(0,0,0);
//     cout  << fixed << setprecision(2) << minn;
// }
//所谓状压，就是将状态压缩成一个数字，以此数字的二进制（01串）表示此状态 
// 真正好做法，状压dp,时间复杂度为O(N * N * pow(2,N));
#include <bits/stdc++.h>
#define ld long double
#define pll pair<ld,ld>
using namespace std;
const int N = 16;
int n;
ld dis[20][20];//存储两个点之间的距离
pll a[20];//存储点
ld dp[1 << N][N];
// dp[mask][i] 表示经过的奶酪集合状态为 mask，当前停留在第 i 块奶酪时已经经过最小距离，此时我们只要考虑那些未经过的点就行
//mask：一个整数，代表当前哪些奶酪被吃掉了（状态）
//i：一个整数，代表老鼠当前停在第 i 块奶酪上。
//值：dp[mask][i] 存储的是达到这个状态所走过的最小距离。
//转移：dp[next_mask][j] = min(dp[next_mask][j], dp[mask][i] + dist(i, j))
ld distance(pll p1,pll p2)//计算距离
{
    ld ans = (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
    ans = pow(ans, 0.5);
    return ans;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n;i++)
        cin >> a[i].first >> a[i].second;
    a[0] = make_pair(0.0, 0.0);
    // 1. 预处理所有点之间的距离 (包括起点)
    for (int i = 0; i <= n;i++)
    {
        for (int j = 0; j <= n;j++)
        {
            dis[i][j] = distance(a[i], a[j]);
        }
    }
    // 2. 初始化 DP 数组为极大值
    //这里对于j来说，不用处理0的情况，因为在过程中不可能再跳到原点
    for (int i = 0; i < (1 << n);i++)
    {
        for (int j = 1; j <= n;j++)
            dp[i][j] = 1e18;
    }
    // 3. 初始状态：从起点到第一块奶酪
    for (int i = 1; i <= n;i++)
    {
        dp[1 << (i - 1)][i] = dis[0][i];
    }
    // 4. 状压 DP 转移
    for (int mask = 1; mask < (1 << n);mask++)// 遍历所有状态，用二进制表示是否选择,此时mask一共有二进制n位(0 ~ n - 1)
    {
        for (int i = 1; i <= n;i++)// 当前在第 i 块奶酪
        {
            if(!mask & (1 << (i - 1)))//如果mask的选择状态下，i没到达过，就跳过，寻找那些二进制位1的点
                continue;
            for (int j = 1; j <= n;j++)//找到了i，接下来遍历每一个没经过的点
            {
                if(mask & (1 << (j - 1)))//如果点j已经到达过，就不处理
                    continue;
                int nextmask = mask | (1 << (j - 1));//标记点j已经到达过
                // 状态转移：从 i 走到 j
                dp[nextmask][j] = min(dp[nextmask][j], dp[mask][i] + dis[i][j]);//原先值与当前值作比较，保证最小
            }
        }
    }
    ld ans = 1e18;
    for (int i = 1; i <= n;i++)
    {
        ans = min(ans, dp[(1 << n) - 1][i]); // 遍历终点情况，取最小值
    }
    cout << fixed << setprecision(2) << ans;
}