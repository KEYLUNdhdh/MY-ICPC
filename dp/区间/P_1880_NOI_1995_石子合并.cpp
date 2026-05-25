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
typedef tuple<int, int, int> piii;
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

void solve()
{
    int n;
    cin >> n;
    vector<i64> m(2 * n + 1, 0), prefix(2 * n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> m[i];
        prefix[i] = prefix[i - 1] + m[i];
    }
    for (int i = n + 1; i <= 2 * n;i++)
    {
        m[i] = m[i - n];
        prefix[i] = prefix[i - 1] + m[i];
    }
    vector<vector<i64>> minn(2 * n + 1, vector<i64>(2 * n + 1, INF));
    vector<vector<i64>> maxx(2 * n + 1, vector<i64>(2 * n + 1, 0));
    for(int i = 1; i <= 2 * n;i++)
        minn[i][i] = 0;
    for (int len = 2; len <= n;len++)
    {
        for (int i = 1; i <= 2 * n;i++)
        {
            int j = i + len - 1;
            if(j > 2 * n)
                break;
            for (int k = i; k < j;k++)
            {
                chmin(minn[i][j], minn[i][k] + minn[k + 1][j] + prefix[j] - prefix[i - 1]);
                chmax(maxx[i][j], maxx[i][k] + maxx[k + 1][j] + prefix[j] - prefix[i - 1]);

            }  
        }
    }

    i64 mn = INF, mx = 0;
    for (int i = 1; i <= n;i++)
    {
        chmin(mn, minn[i][i + n - 1]);
        chmax(mx, maxx[i][i + n - 1]);
    }
    cout << mn << "\n" << mx;
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