#include <bits/stdc++.h>
using namespace std;
int n, m, sx, sy;
const int MAXN = 1600;
char c[MAXN][MAXN];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int vis[MAXN][MAXN][2];
int used[MAXN][MAXN];
int flag = 0;
void dfs(int rx,int ry,int x,int y)
{
    if(flag)
        return;
    //非常精妙的一个点，先进入递归再回溯，给我们机会判断是否已经到达相对位置了
    if(used[x][y])
    {
        if(vis[x][y][0] != rx || vis[x][y][1] != ry)
        {
            flag = 1;
        }
        return;
    }
    used[x][y] = 1;
    vis[x][y][0] = rx;
    vis[x][y][1] = ry;
    for (int i = 0; i < 4;i++)
    {
        int rnx = rx + dx[i];
        int rny = ry + dy[i];
        //nx,ny保证在范围内
        int nx = (rnx % n + n) % n;
        int ny = (rny % m + m) % m;
        if(c[nx][ny] != '#')
        {
            dfs(rnx, rny, nx, ny);
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(cin >> n>> m)
    {
        char tp;
        for (int i = 0; i < n;i++)
        {
            for (int j = 0; j < m;j++)
            {
                cin >> tp;
                c[i][j] = tp;
                if(tp == 'S')
                    sx = i, sy = j;
            }
        }
        flag = 0;
        memset(vis, 0, sizeof vis);
        memset(used, 0, sizeof used);
        dfs(sx, sy, sx, sy);
        if(flag)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}