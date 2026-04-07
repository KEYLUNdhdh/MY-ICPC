#include <bits/stdc++.h>
using namespace std;
int n, m, t;
int sx, sy, fx, fy;
int mine[7][7] = {0};
int vis[7][7] = {0};
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int cnt = 0;
void dfs(int x,int y)
{
    if(x == fx && y == fy)
    {
        cnt++;
        return;
    }
    for (int i = 0; i < 4;i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && mine[nx][ny] != 1)
        {
            vis[nx][ny] = 1;
            dfs(nx, ny);
            vis[nx][ny] = 0;
        }
    }
}
int main()
{
    // cout << "ggg";
    cin >> n >> m >> t;
    cin >> sx >> sy >> fx >> fy;
    int i, j;
    for (int k = 0; k < t;k++)
    {
        cin >> i >> j;
        mine[i][j] = 1;
    }
    vis[sx][sy] = 1;
    dfs(sx,sy);
    cout << cnt;
}