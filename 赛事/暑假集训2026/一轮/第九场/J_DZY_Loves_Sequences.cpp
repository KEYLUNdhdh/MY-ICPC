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
// bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    // debugarr(a)
    // vector<int> ans(n + 1, 0);
    vector<i64> pre(n + 1, 0);
    pre[1] = 1;
    for (int i = 2; i <= n;i++)
    {
        if(a[i] > a[i - 1])
            pre[i] = pre[i - 1] + 1;
        else
            pre[i] = 1;
    }
    vector<i64> suf(n + 1, 0);
    suf[n] = 1;
    a.push_back(INF);
    for (int i = n - 1; i >= 1;i--)
    {
        if(a[i] < a[i + 1])
            suf[i] = suf[i + 1] + 1;
        else
            suf[i] = 1;
    }

    i64 ans = 0;
    // debugarr(pre)
        // debugarr(suf)
        suf.push_back(0);
    for (int i = 1; i <= n;i++)
    {
        chmax(ans, pre[i - 1] + 1);
        chmax(ans, suf[i + 1] + 1);
        int p = a[i - 1];
        int s = a[i + 1];
        // debug(a[i])
        // debug(pre[i])
        // debug(suf[i])
        if(p + 1 < s)
            chmax(ans, pre[i - 1] + suf[i + 1] + 1);

        // debug(ans)
    }

    cout << ans;
}

// bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}