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

int Kadane(vector<int> a)
{
    int maxx = 0, now = 0;
    for (int i = 1; i < a.size();i++)
    {
        now += a[i];
        maxx = max(maxx, now);
        if(now < 0)
            now = 0;
    }

    return maxx;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    int maxx = -INF;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        chmax(maxx, a[i]);
    }

    if(maxx <= 0)
    {
        cout << maxx << "\n";
        return;
    }

    int ans = 0, now = 0;
    for (int i = 1; i <= n;i++)
    {
        if(i == 1)
            now += a[i];
        else if(i != 1 && abs(a[i] - a[i - 1]) % 2)
            now += a[i];
        else
            now = a[i];
        // debug(i)
        // debug(now)
        ans = max(ans, now);
        if(now < 0)
            now = 0;
    }

    cout << ans << "\n";
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