#include <bits/stdc++.h>
using namespace std;
int dis[105][105];
const int INF =  1e9;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    while (n != 0 && m != 0)
    {
        //初始化
        for (int i = 1; i <= n;i++)
        {
            for (int j = 1; j <= n;j++)
            {
                if (i == j)
                {
                    dis[i][j] = 0;
                }
                else
                dis[i][j] = INF;
            }
        }
        //读入
        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            if (c < dis[a][b])
            {
                dis[a][b] = c;
                dis[b][a] = c;
            }
        }
        //操作,以k位中转，遍历每个i，j两个节点，找最小值
        for (int k = 1; k <= n;k++)
            for (int i = 1; i <= n;i++)
                for (int j = 1; j <= n;j++)
                {
                    if (dis[i][k] != INF && dis[k][j] != INF)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
        cout << dis[1][n] << "\n";
        cin >> n >> m;
    }
}