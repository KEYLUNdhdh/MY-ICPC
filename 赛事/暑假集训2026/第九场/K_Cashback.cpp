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

template<typename T,typename F>
struct STable
{
    int n;
    int maxlog;
    vector<vector<T>> st;
    F func;
    //a 1 - index
    STable(const vector<T>& a,const F& f) : func(f)
    {
        n = a.size() - 1;
        maxlog = __lg(n) + 1;
        st.assign(n + 1, vector<T>(maxlog));
        for (int i = 1; i <= n;i++)
            st[i][0] = a[i];
        for (int j = 1; j < maxlog;j++)
        {
            int len = 1 << (j - 1);
            for (int i = 1;i <= n - (1 << j) + 1;i++)
                st[i][j] = func(st[i][j - 1], st[i + len][j - 1]);
        }
    }
    inline T query(int l,int r) const
    {
        if (l > r) 
            swap(l, r);
        int k = __lg(r - l + 1);
        return func(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

// 其实感觉是 1 -> c - 1 是等价的，我们归约到 1
// 那么分界点就是c
// 所以 c -> 2 * c - 1 也是等价的。 c
// 那其实可以分段了
// 但是如果 c 是 1 时间复杂度不行啊
// 只枚举 c/1 ？ 
// 好像可以，感觉减去两个不如减去一个
// 他妈的最小啊
void solve()
{
    int n, c;
    cin >> n >> c;

    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    vector<i64> prefix(n + 1, 0);
    for (int i = 1; i <= n;i++)
        prefix[i] = prefix[i - 1] + a[i];
    STable st(a, [](i64 a, i64 b) { return min(a, b); });
    vector<i64> dp(n + 1, 0);

    for (int i = 1; i <= n;i++)
    {
        if(c != 1)
            dp[i] = a[i] + dp[i - 1];
        else
            dp[i] = dp[i - 1];
        if(i >= c)
        {
            chmin(dp[i], dp[i - c] - st.query(i - c + 1, i) + prefix[i] - prefix[i - c]);
        }
    }
    // debugarr(dp)
    cout << dp[n];
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