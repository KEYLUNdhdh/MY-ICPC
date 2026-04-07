#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 35;
int a[N][N] = {0};
int reach[N][N];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(int x,int y)
{
    reach[x][y] = 1;
    for (int i = 0; i < 4;i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 0 && nx < n && ny >= 0 && ny < n && !reach[nx][ny] && !a[nx][ny])
        {
            reach[nx][ny] = 1;
            dfs(nx, ny);
        }
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n;i++)
        for (int j = 0; j < n;j++)
            cin >> a[i][j];
    for (int i = 0; i < n;i++)
    {
        if(a[0][i] == 0 && reach[0][i] == 0)
        dfs(0,i);
        if(a[n - 1][i] == 0 && reach[n - 1][i] == 0)
        dfs(n - 1, i);
        if(a[i][0] == 0 && reach[i][0] == 0)
        dfs(i, 0);
        if(a[i][n - 1] == 0 && reach[i][n - 1] == 0)
        dfs(i, n - 1);
    }
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n;j++)
        {
            if(reach[i][j])
                cout << "0 ";
            else if(a[i][j] == 1)
            {
                cout << "1 ";
            }
            else
            {
                cout << "2 ";
            }
        }
        cout << "\n";
    }
}