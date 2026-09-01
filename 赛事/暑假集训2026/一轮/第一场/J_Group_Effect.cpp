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
constexpr i64 MOD = 998244353, INF = 1e9;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void solve()
{
    int n, m;
    cin >> n >> m;
    i64 da, db;
    cin >> da >> db;

    vector<vector<char>> mat(n + 1, vector<char>(m + 1, '\0'));
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= m;j++)
            cin >> mat[i][j];

    vector<vector<char>> ans(n + 1, vector<char>(m + 1, '\0'));
    i64 res = 0;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            if(mat[i][j] == '#')
            {
                ans[i][j] = '#';
                continue;
            }

            int ind = 0;
            for (int k = 0; k < 4;k++)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && mat[nx][ny] == '.')
                    ind++;
            }

            i64 upa = da + ind;
            i64 upb = db - ind;
            if(upa >= upb)
            {
                res += upa;
                ans[i][j] = 'A';
            }
            else
            {
                res += upb;
                ans[i][j] = 'B';
            }
        }
    }

    cout << res << "\n";
    for (int i = 1; i <= n;i++)
    {
        for(int j = 1; j<= m;j++)
            cout << ans[i][j];
        cout << "\n";
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