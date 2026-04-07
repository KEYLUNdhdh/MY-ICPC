#include <bits/stdc++.h>
#define pii pair<int,int>
#define int long long
using namespace std;
const int M = 5e4 + 5;
int m;
typedef struct kkk{
    int x, y, t;
}kkk;
kkk k[M];
int dx[] = {0, 1, 0, -1,0};
int dy[] = {1, 0, -1, 0,0};
int check[400][400];
int minstep[400][400];
void bfs()
{
    queue<pii> q;
    q.push(make_pair(0, 0));
    minstep[0][0] = 0;
    while(!q.empty())
    {
        pii cur = q.front();
        q.pop();
        if(check[cur.first][cur.second] >= 0x3f3f3f3f)
        {
            cout << minstep[cur.first][cur.second];
            return;
        }
        for (int i = 0; i < 4;i++)
        {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx >= 0 && nx <= 305 && ny >= 0 && ny <= 305 && minstep[nx][ny] == -1)
            {
                minstep[nx][ny] = minstep[cur.first][cur.second] + 1;
                if(minstep[nx][ny] >= check[nx][ny])
                {
                    minstep[nx][ny] = -2;
                    continue;
                }
                q.push(pii(make_pair(nx, ny)));
            }
        }
    }
    cout << -1;
    return;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    memset(check,0x3f3f3f3fll, sizeof(check));
    memset(minstep, -1ll, sizeof(minstep));
    cin >> m;
    for (int i = 0; i < m;i++)
    {
        cin >> k[i].x >> k[i].y >> k[i].t;
    }
    for (int i = 0; i < m;i++)
    {
        for (int j = 0; j < 5;j++)
        {
            int nx = k[i].x + dx[j];
            int ny = k[i].y + dy[j];
            if(nx >= 0 && nx <= 305 && ny >= 0 && ny <= 305 &&check[nx][ny] > k[i].t)
            {
                check[nx][ny] = k[i].t;
            }
        }
    }
    bfs();
}