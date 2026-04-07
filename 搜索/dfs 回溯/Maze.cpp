#include <bits/stdc++.h>
using namespace std;
int n, m, k;
char maze[505][505] = {'\0'};
int vis[505][505] = {0};
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
 
void dfs(int tpn,int tpm)
{
    vis[tpn][tpm] = 1;
    //迷宫搜索
    for (int i = 0; i < 4;i++)
    {
        int nx = tpn + dx[i];
        int my = tpm + dy[i];
        if(nx >= 1 && nx <= n && my >= 1 && my <= m && maze[nx][my] == '.' && !vis[nx][my])
        {
            dfs(nx, my);
        }
    }
    // vis[n][m] = 0;
    //没得走了就可以填充了，这时候一定可以填充。因为是从末端向前填充，剩余‘.’一定可以联通
    if(k > 0)
    {
        maze[tpn][tpm] = 'X';
        k--;
    }
}  

int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m >> k;
    int posn = 0x3f3f3f3f, posm = 0x3f3f3f3f;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            cin >> maze[i][j];
        }
    }
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            if(maze[i][j] == '.')
            {
                posn = i;
                posm = j;
                break;
            }
        }
        if(posn != 0x3f3f3f3f)
            break;
    }
    dfs(posn, posm);
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            cout << maze[i][j];
        }
        cout << "\n";
    }

}