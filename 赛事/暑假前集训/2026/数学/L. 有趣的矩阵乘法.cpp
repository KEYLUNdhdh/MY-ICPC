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
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<i64>> list(n + 1, vector<i64>(m + 1, 0));
    for (int k = 1; k <= n;k++)
    {
        for (int i = 1; i <= m;i++)
        {
            for (int j = 1; j <= m;j++)
            {
                i64 ele;
                cin >> ele;
                list[k][j] = (list[k][j] + ele) % MOD;
            }
        }
    }

    while(q--)
    {
        int x, y;
        i64 k;
        cin >> x >> y >> k;

        if(x != y)
        {
            for (int i = 1; i <= n;i++)
                list[i][y] = (list[i][y] + list[i][x] * k) % MOD;
        }
        else
        {
            for (int i = 1; i <= n;i++)
                list[i][x] = (list[i][x] * k) % MOD;
        }

    }

    
    for (int i = 1; i <= n;i++)
    {
        i64 ans = 0;

        for (int j = 1; j <= m;j++)
            ans = (ans + list[i][j]) % MOD;

        cout << (ans + MOD) % MOD << "\n";
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