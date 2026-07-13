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

void solve()
{
    int n;
    cin >> n;
    vector<int> b(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> b[i];

    vector<array<int, 2>> dp(n + 1, {0, 0});
    vector<int> ok(n + 1, 0);

    vector<vector<int>> mp(n + 1);

    for (int i = 1; i <= n; i++)
    {
        i64 pos = i + b[i];

        if (pos <= n)
            mp[pos].push_back(i);
    }


    dp[0][0] = 1;
    ok[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        // dp[i][0]
        int len = b[i];
        int pos = i - len - 1;

        if(pos >= 0  && ok[pos])
            dp[i][0] = 1;

        if(i + len <= n && ok[i - 1])
            dp[i][1] = 1;

        if(dp[i][0])
            ok[i] = 1;

        if(!ok[i])
        {
            for(int k : mp[i])
            {
                if(dp[k][1])
                {
                    ok[i] = 1;
                    break;
                }
            }
        }
    }

    int f = ok[n];

    if(f)
        cout << "YES\n";
    else
        cout << "NO\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}