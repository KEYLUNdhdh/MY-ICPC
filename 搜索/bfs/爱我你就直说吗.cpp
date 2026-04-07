#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
const int MOD = 998244353;
//bfs 剥洋葱
void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    // s = "#" + s;
    int len = s.size();
    vector<vector<int>> a(n + 1, vector<int>(n + 1, -1));
    queue<pii> q;
    for (int i = 1; i <= n;i++)
    {
        if(i != 1 && i != n && i !=(n + 1) / 2)
        {
            a[1][i] = 0;
            q.push({1, i});
        }
        else
        {
            a[2][i] = 0;
            q.push({2, i});
        }
    }
    for (int i = 3; i <= (n - 1) / 2 + 1;i++)
    {
        a[i][1] = 0, a[i][n] = 0;
        q.push({i, 1}), q.push({i, n});
    }
    for (int k = 1; k <= (n - 1) / 2;k++)
    {
        int base = (n - 1) / 2 + 1;
        int hang = base + k;
        a[hang][1 + k] = 0;
        a[hang][n - k] = 0;
        q.push({hang, 1 + k});
        q.push({hang, n - k});
    }
    auto isheart = [&](int x, int y) -> bool
    {
        int base = (n - 1) / 2 + 1;
        if(x == 1 || x == n)
            return false;
        if(x == 2 && (y == 1 || y == n || y == (n + 1) /2))
            return false;
        if(x > base)
        {
            int ju = x - base;
            if(y < ju + 1 || y > n - ju)
                return false;
            else
                return true;
        }
        return true;
    };
    vector<int> dx = {0, 0, 1, -1};
    vector<int> dy = {1, -1, 0, 0};
    while(!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4;i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= n && a[nx][ny] == -1 && isheart(nx,ny))
            {
                a[nx][ny] = a[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            if(a[i][j] == -1)
                cout << "-";
            else
                cout << s[a[i][j] % len];
        }
        cout << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}