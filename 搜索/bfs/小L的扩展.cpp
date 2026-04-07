#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
#define lyc_fan_club main
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
template<class T>
void chmax(T &a, T b) {
    if (a < b) {
        a = b;
    }
}
template<class T>
void chmin(T &a, T b) {
    if (a > b) {
        a = b;
    }
}
const int MOD = 998244353;
//优先队列 bfs
//edu: 考察搜索算法的运用。
// 在传统的多源起点 bfs 的基础上，手动设置一些优先级别靠后的点，使用优先队列代替
// 队列维护 bfs 即可。
void solve()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<int>> vec(n + 1, vector<int>(m + 1, -1));
    vector<vector<int>> blue(n + 1, vector<int>(m + 1, -1));
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    struct node{
        int x, y, t;
        bool operator>(const node& b) const
        {
            return t > b.t;
        }
    };
    priority_queue<node, vector<node>, greater<node>> pq;
    for (int i = 0; i < a;i++)
    {
        int x, y;
        cin >> x >> y;
        vec[x][y] = 0;
        pq.push({x, y, 0});
    }
    for (int i = 0; i < b;i++)
    {
        int x, y, t;
        cin >> x >> y >> t;
        blue[x][y] = t;
    }
    while(!pq.empty())  
    {
        node now = pq.top();
        pq.pop();
        if(now.t > vec[now.x][now.y] && vec[now.x][now.y] != -1)
            continue;
        for (int i = 0; i < 4;i++)
        {
            int nx = now.x + dx[i];
            int ny = now.y + dy[i];
            if(nx >= 1 && nx <= n && ny >=1  && ny <= m)
            {
                int nt = max(now.t + 1, blue[nx][ny]);
                if(vec[nx][ny] == -1 || nt < vec[nx][ny])
                {
                    vec[nx][ny] = nt;
                    pq.push({nx, ny, nt});
                }
            }
        }
    }
    int maxx = 0;
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= m;j++)
            chmax(maxx, vec[i][j]);
    cout << maxx;
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}