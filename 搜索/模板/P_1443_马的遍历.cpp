// #include <bits/stdc++.h>
// #define int long long
// using namespace std;
// int n, m, x, y;
// int minstep[405][405] = {0};
// int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
// int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
// void dfs(int p,int q,int step)
// {
//     if(p < 1 || p > n || q < 1 || q > m)
//         return;
//     if (minstep[p][q] <= step)
//         return;
//     minstep[p][q] = step;
//     for (int i = 0; i < 8;i++)
//     {
//         int np = p + dx[i];
//         int nq = q + dy[i];
//         if(np >= 1 && np <= n && nq >= 1 && nq <= m)
//         {
//             dfs(np, nq, step + 1);
//         }
//     }
// }
// signed main()
// {
//     memset(minstep, (long long)0x3f3f3f3f, sizeof(minstep));
//     cin >> n >> m >> x >> y;
//     dfs(x, y, 0);
//     for (int i = 1; i <= n;i++)
//     {
//         for (int j = 1; j <= m;j++)
//         {
//             if(minstep[i][j] >= 0x3f3f3f3f)
//             {
//                 cout << -1 << " ";
//             }
//             else
//             {
//                 cout << minstep[i][j] << " ";
//             }
//         }
//         cout << "\n";
//     }
// }
//  寻找最短路一般就bfs
//bfs is right
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
int m, n, x, y;
int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
int minstep[405][405] = {0};
queue<pii> q;
void bfs()
{
    minstep[x][y] = 0;
    q.push(pii(make_pair(x, y)));
    while(!q.empty())
    {
        pii cur = q.front();
        q.pop();
        for (int i = 0; i < 8;i++)
        {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx >= 1 && nx<= n && ny >=1 && ny <= m)
            {
                if(minstep[nx][ny] == -1)
                {
                    minstep[nx][ny] = minstep[cur.first][cur.second] + 1;
                    q.push(pii(make_pair(nx,ny)));
                }
            }
        }
    }
}
int main()
{
    cin >> n >> m >> x >> y;
    memset(minstep, -1, sizeof(minstep));
    bfs();
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            cout << minstep[i][j] << " ";
        }
        cout << "\n";
    }
}