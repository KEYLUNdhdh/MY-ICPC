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
// P_1757_通天之分组背包

void solve()
{
    int m, n;
    cin >> m >> n;

    vector<i64> dp(m + 1, 0);
    map<int, vector<pll>> mp;
    for (int i = 0; i < n;i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        mp[c].push_back({a, b});
    }

    //以下枚举的顺序不能变化！！！
    //这样能够严格保证每组只选一个
    for(auto [idx, vec]: mp)// 循环每一组
    {
        for (int i = m; i >= 0;i--)// 循环背包容量
        {
            // 我们盯着剩余容量 i，然后用最内层的[c, w]扫视这组内的所有物品。
            //我们在这些选项中，挑出一个最大值，更新给 dp[i]。
            //这就保证了只选一个
            for(auto &[c, w] : vec)// 循环该组的每一个物品
            {
                if(i >= c)// 背包容量充足
                    chmax(dp[i], dp[i - c] + w);// 像0-1背包一样状态转移
            }
        }
    }

    cout << dp[m];
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