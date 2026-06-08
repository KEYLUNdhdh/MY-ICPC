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
constexpr i64 MOD = 1e9 + 7, INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> seq(m + 1, vector<int>(n + 1, 0));
    map<int, int> mp;
    for (int i = 1;i <= m;i++)
        for (int j = 1; j <= n;j++)
        {
            if(i == 1)
            {
                cin >> seq[i][j];
                mp[seq[i][j]] = j;
                seq[i][j] = j;
            }
            else
            {
                cin >> seq[i][j];
                seq[i][j] = mp[seq[i][j]];
            }
        }

    vector<vector<int>> val(n + 1, vector<int>(n + 1, 0));
    for (int k = 1; k <= m;k++)
    {
        vector<int> pos(n + 1, 0);
        for (int i = 1; i <= n;i++)
            pos[seq[k][i]] = i;
        
        deque<int> minn, maxx;
        for (int l = 1; l <= n; l++)
        {
            int lpos = pos[l];
            int minn = l, maxx = l; 
            for (int r = l; r <= n; r++)
            { 
                if (lpos + r - l > n)
                    continue;

                chmin(minn, seq[k][lpos + r - l]);
                chmax(maxx, seq[k][lpos + r - l]);

                if (minn == l && maxx == r)
                    val[l][r]++;
            }
        }
    }
    for (int l = 1; l <= n; l++)
        for (int r = l; r <= n; r++)
            if(val[l][r] == m)
                val[l][r] = 1;
            else
                val[l][r] = 0;
    vector<vector<i64>> dp(n + 1, vector<i64>(n + 1, 1));
    vector<vector<i64>> forest(n + 1, vector<i64>(n + 1, 1));
    for (int len = 1; len <= n;len++)
    {
        for (int l = 1; l <= n;l++)
        {
            int r = l + len - 1;
            if(r > n)
                break;
            
            if(val[l][r])
                dp[l][r] = ((l + 1 <= n) ? forest[l + 1][r] : 1);
            else
                dp[l][r] = 0;

            forest[l][r] = 0;
            for (int k = l; k <= r;k++)
                forest[l][r] = (forest[l][r] + dp[l][k] * ((k + 1 <= n) ? forest[k + 1][r] : 1)) % MOD;
        }
    }

    cout << dp[1][n];
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