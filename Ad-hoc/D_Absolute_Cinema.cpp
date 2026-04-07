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


void solve()
{
    i64 n;
    cin >> n;
    vector<i64> f(n + 1), a(n + 1);
    for (i64 i = 1; i <= n;i++)
        cin >> f[i];
    int prefix = 0;
    auto getk = [&](int k)
    {
        i64 lw = f[k - 1] - f[k];
        i64 up = f[k] - f[k + 1];
        i64 de = lw - up;
        return de / 2;
    };
    for(int i = 2; i <= n - 1;i++)
        a[i] = getk(i);
    i64 p = f[1];
    i64 sum = 0;
    for (int i = 2; i <= n - 1;i++)
    {
        p -= a[i] * (i - 1);
        sum += a[i];
    }
    a[n] = p / (n - 1);
    a[1] = (-1) * (f[1] - f[2] - sum - a[n]);
    for (int i = 1; i <= n;i++)
        cout << a[i] << " ";
    cout << "\n";
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