// //bfs才是对的
// #include <bits/stdc++.h>
// #define pii pair<int,int>
// #define piiii pair<pair<int,int>,pair<int,int>>
// using namespace std;
// map<char,piiii> mp;
// int n, m, fx, fy, sx, sy;
// const int N = 305;
// char a[N][N] = {'\0'};
// int vis[N][N] = {0};
// int dx[] = {-1, 0, 1, 0};
// int dy[] = {0, 1, 0, -1};
// int ans = 0x3f3f3f3f;
// void dfs(int x,int y,int step,int ava)
// {
//     if(x == fx && y == fy)
//     {
//         ans = min(ans, step);
//         return;
//     }
//     for (int i = 0; i < 4;i++)
//     {
//         int nx = x + dx[i];
//         int ny = y + dy[i];
//         if(nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] != '#'&& !vis[nx][ny])
//         {
//             if(a[nx][ny] == '.' || a[nx][ny] == '=')
//             {
//                 vis[nx][ny] = 1;
//                 dfs(nx, ny,step + 1, 1);
//                 vis[nx][ny] = 0;
//             }
//             else
//             {
//                 if(ava)
//                 {
//                     if(nx == mp[a[nx][ny]].first.first && ny ==mp[a[nx][ny]].first.second)
//                     {
//                         vis[mp[a[nx][ny]].second.first][mp[a[nx][ny]].second.second] = 1;
//                         dfs(mp[a[nx][ny]].second.first, mp[a[nx][ny]].second.second, step + 1, 0);
//                         vis[mp[a[nx][ny]].second.first][mp[a[nx][ny]].second.second] = 0;
//                     }
//                     else
//                     {
//                         vis[mp[a[nx][ny]].first.first][mp[a[nx][ny]].first.second] = 1;
//                         dfs(mp[a[nx][ny]].first.first, mp[a[nx][ny]].first.second, step + 1, 0);
//                         vis[mp[a[nx][ny]].first.first][mp[a[nx][ny]].first.second] = 0;
//                     }
//                 }
//             }
//         }
//     }
// }
// int main()
// {
//     cin >> n >> m;
//     for (int i = 0; i < n;i++)
//     {
//         for (int j = 0; j < m;j++)
//         {
//             cin >> a[i][j];
//             if (a[i][j] >= 'A' &&a[i][j] <= 'Z')
//             {
//                 if(mp.count(a[i][j]))
//                 {
//                     mp[a[i][j]].second.first = i;
//                     mp[a[i][j]].second.second = j;
//                 }
//                 else
//                 {
//                     mp[a[i][j]].first.first = i;
//                     mp[a[i][j]].first.second = j;
//                 }
//             }
//             else if(a[i][j] == '=')
//             {
//                 fx = i;
//                 fy = j;
//             }
//             else if(a[i][j] == '@')
//             {
//                 sx = i;
//                 sy = j;
//             }
//         }
//     }
//     vis[sx][sy] = 1;
//     dfs(sx, sy,0,1);
//     cout << ans;
// }

#include <bits/stdc++.h>
using namespace std;

const int N = 305;
char g[N][N];
int dist[N][N]; // 记录到每个点的最短距离
int n, m, sx, sy, ex, ey;
struct Point { int x, y; };
vector<Point> portal[26]; // 存储 A-Z 传送门的位置

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            if (g[i][j] == '@') { sx = i; sy = j; }
            else if (g[i][j] == '=') { ex = i; ey = j; }
            else if (g[i][j] >= 'A' && g[i][j] <= 'Z') {
                portal[g[i][j] - 'A'].push_back({i, j});//重点掌握
            }
        }
    }
    //这个memset挺新的
    memset(dist, -1, sizeof dist);
    queue<Point> q;
    q.push({sx, sy});
    dist[sx][sy] = 0;

    int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.x == ex && curr.y == ey) {
            cout << dist[curr.x][curr.y] << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i], ny = curr.y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] != '#') {
                int tx = nx, ty = ny;
                
                // 如果踩到传送门，强制传送到另一端,重点掌握写法
                if (g[nx][ny] >= 'A' && g[nx][ny] <= 'Z') {
                    auto& p = portal[g[nx][ny] - 'A'];
                    if (p[0].x == nx && p[0].y == ny) {
                        tx = p[1].x; ty = p[1].y;
                    } else {
                        tx = p[0].x; ty = p[0].y;
                    }
                }

                if (dist[tx][ty] == -1) {
                    dist[tx][ty] = dist[curr.x][curr.y] + 1;
                    q.push({tx, ty});
                }
            }
        }
    }
    return 0;
}