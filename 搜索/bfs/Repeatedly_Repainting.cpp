// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
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
#define KEYLUN main
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
void debug_out() { cerr << "\n"; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) { cerr << " " << H; debug_out(T...); }
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char* names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char* names, Head H, Tail... T) {
    while (*names == ' ' || *names == ',') names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i) {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[') bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']') bracket--;
        else if (names[i] == ',' && bracket == 0) break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H) cerr << v << " ";
    cerr << "\n"; 
    
    debugarr_out(names + i + 1, T...);
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template<class T> void chmin(T &a, T b) { if (a > b) a = b; }
template<class T> void chmax(T &a, T b) { if (a < b) a = b; }
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

// # 1 .0
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
void solve()
{
    int h, w;
    cin >> h >> w;

    vector<vector<int>> mat(h + 1, vector<int>(w + 1, 0));
    vector<vector<int>> vis(h + 1, vector<int>(w + 1, inf));

    queue<pii> q;
    for (int i = 1; i <= h;i++)
        for (int j = 1; j <= w;j++)
        {
            char c;
            cin >> c;
            if(c == '#')
            {
                mat[i][j] = 1;
            }

        }

    for (int i = 1; i <= h;i++)
    {
        for (int j = 1; j <= w;j++)
        {
            if(!mat[i][j])
                continue;
            for (int k = 0; k < 8;k++)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if(nx >= 1 && nx <= h && ny >= 1 && ny <= w && mat[nx][ny] == 0)
                {
                    q.push({nx, ny});
                    vis[nx][ny] = 1;
                }
            }
        }
    }

    for (int i = 1; i <= h;i++)
    {
        for (int j = 1; j <= w;j++)
        {
            cerr << mat[i][j];
        }
        cerr << "\n";
    }

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 1 && nx <= h && ny >= 1 && ny <= w && vis[x][y] + 1 < vis[nx][ny])
            {
                vis[nx][ny] = vis[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    for (int i = 1; i <= h;i++)
    {
        for (int j = 1; j <= w;j++)
        {
            cerr << vis[i][j] << " ";
        }
        cerr << "\n";
    }
    for (int i = 1; i <= h;i++)
    {
        for (int j = 1; j <= w;j++)
        {
            if(vis[i][j] == inf)
            {
                cout << '.';
                continue;
            }
            int f = vis[i][j] % 2;
            if(f)
                cout << '.';
            else
                cout << "#";
        }
        cout << "\n";
    }
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}