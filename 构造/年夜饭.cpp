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

//这个数既是第 i 行积的一部分（必须是 a i  的因子），也是第 j 列积的一部分（必须是 b j的因子）。为了尽快“消耗”掉 a i  和 b j中的因子，我们应该在这个格子里填入它们当前所能共有的最大因子，即它们的最大公约数 (GCD)。
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, 0), b(m + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    for (int i = 1; i <= m;i++)
        cin >> b[i];
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            int g = gcd(a[i], b[j]);
            cout << g << " ";
            a[i] /= g;
            b[j] /= g;
        }
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