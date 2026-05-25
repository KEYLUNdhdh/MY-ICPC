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
constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;
    vector<vector<i64>> dp(n + 1, vector<i64>(n + 1, INF));

    for (int i = 1; i <= n;i++)
        dp[i][i] = 0;
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i <= n; i++)
        {
            int j = i + len - 1;
            if(j > n)
                break;
            if(len == 2)
            {
                if(s[i] == s[j])
                    dp[i][j] = 0;
                else
                    dp[i][j] = 1;
            }
            else
            {
                if(s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1];
                else
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
            }
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

// 当 s[i] != s[j] 时，为了让区间 [i, j] 变成回文串，我们有两种选择：

// 迎合左边（在右侧插入）：我们在最右边（j 的后面）插入一个和 s[i] 相同的字符。这样两头就都是 s[i] 匹配上了。此时，我们只需要把中间剩下的 s[i+1 ... j] 变成回文串即可。
// 代价为：dp[i + 1][j] + 1

// 迎合右边（在左侧插入）：我们在最左边（i 的前面）插入一个和 s[j] 相同的字符。这样两头也匹配上了。此时，只需要把剩下的 s[i ... j-1] 变成回文串即可。
// 代价为：dp[i][j - 1] + 1