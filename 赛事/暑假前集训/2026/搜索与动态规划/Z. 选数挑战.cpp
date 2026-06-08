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
constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    int n;
    cin >> n;

    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    int q;
    cin >> q;

    vector<vector<vector<int>>> memo(51, vector<vector<int>>(51, vector<int>(51, -1)));

    while(q--)
    {
        int x, y, z;
        cin >> x >> y >> z;

        vector<int> tmp = {x, y, z};
        sort(tmp.begin(), tmp.end());

        x = tmp[0], y = tmp[1], z = tmp[2];
        if(memo[x][y][z] != -1)
        {
            if(memo[x][y][z])
                cout << "Yes\n";
            else
                cout << "No\n";

            continue;
        }

        vector<i128> dp(11, 0);
        dp[0] = 1;
        for (int i = 1; i <= n;i++)
        {
            if(i == x || i == y || i == z)
                continue;

            if(a[i] > 87)
                continue;

            for (int c = 10; c >= 1;c--)
            {
                dp[c] |= (dp[c - 1] << a[i]);
            }
        }
        int ans = (dp[10] >> 87) & 1;
        memo[x][y][z] = ans;
        if(ans)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
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