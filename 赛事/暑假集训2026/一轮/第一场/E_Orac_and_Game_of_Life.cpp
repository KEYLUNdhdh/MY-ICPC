#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr i64 MOD = 998244353, INF = 2e18;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
void solve()
{
    int n, m, t;
    cin >> n >> m >> t;

    vector<vector<int>> mat(n + 1, vector<int>(m + 1, -1));
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= m;j++)
        {
            char c;
            cin >> c;
            mat[i][j] = c - '0';
        }


    // for (int i = 1; i <= n;i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //         cerr << mat[i][j] << " ";
    //     cerr << "\n";
    // }
    queue<pii> q;
    vector<vector<i64>> first(n + 1, vector<i64>(m + 1, INF));
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            int cur = mat[i][j];
            for (int k = 0; k < 4;k++)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && mat[nx][ny] == cur)
                {
                    first[i][j] = 0;
                    q.push({i, j});
                    first[i + dx[k]][j + dy[k]] = 0;
                    break;
                }
            }
        }
    }

    while(!q.empty())
    {
        int len = q.size();
        while(len--)
        {
            auto [i, j] = q.front();
            q.pop();
            for (int k = 0; k < 4;k++)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && first[nx][ny] == INF)
                {
                    first[nx][ny] = first[i][j] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    // for (int i = 1; i <= n;i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //         cerr << first[i][j] << " ";
    //     cerr << "\n";
    // }
    while (t--)
    {
        i64 i, j, p;
        cin >> i >> j >> p;

        i64 s = first[i][j];
        // debug(s)
        // debug()
        // cutline
        
        if (p < s)
            cout << mat[i][j] << "\n";
        else
        {
            int times = (p - s) % 2;
            cout << (mat[i][j] ^ times) << "\n";
        }
    }
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
