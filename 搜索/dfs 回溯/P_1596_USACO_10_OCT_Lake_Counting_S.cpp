#include <bits/stdc++.h>
using namespace std;
const int N = 105;
char c[N][N] = {'\0'};
int vis[N][N] = {0};
int checkall[N][N] = {0};
int n, m;
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
void dfs(int x,int y)
{
    for (int i = 0; i < 8;i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && c[nx][ny] == 'W')
        {
            vis[nx][ny] = 1;
            dfs(nx, ny);
        }
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < m;j++)
        {
            cin >> c[i][j];
        }
    }
    int cnt = 0;
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < m;j++)
        {
            if(!vis[i][j] && c[i][j] == 'W')
            {
                vis[i][j] = 1;
                dfs(i, j);
                cnt++;
            }
        }   
    }
    cout << cnt;
}