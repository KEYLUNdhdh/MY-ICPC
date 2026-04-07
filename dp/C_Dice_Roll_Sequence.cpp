#include <bits/stdc++.h>
#define lyc_fan_club main
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
template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
const int MOD = 998244353;

//
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
    }
    vector<int> dp(7, 0);
    for (int i = 1; i <= 6;i++)
    {
        dp[i] = (a[0] == i ? 0 : 1);
    }
    for (int i = 1; i < n;i++)
    {
        vector<int> nxt(7, 1e9);
        for (int pre = 1; pre <= 6;pre++)
        {
            for (int now = 1; now <= 6;now++)
            {
                if(pre != now && pre + now != 7)
                {
                    nxt[now] = min(nxt[now], dp[pre] + (a[i] == now ? 0 : 1));
                }
            }
        }
        dp = nxt;
    }
    int minn = 1e9;
    for (int i = 1; i <= 6;i++)
        chmin(minn, dp[i]);
    cout << minn << "\n";
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