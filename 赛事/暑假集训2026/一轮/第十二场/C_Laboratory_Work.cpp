// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
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
#define KEYLUN main
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
void debug_out() { cerr << "\n"; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) { cerr << " " << H; debug_out(T...); }
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char* names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char* names, Head H, Tail... T) {
    while (*names == ' ' || *names == ',') names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i) {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[') bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']') bracket--;
        else if (names[i] == ',' && bracket == 0) break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H) cerr << v << " ";
    cerr << "\n"; 
    
    debugarr_out(names + i + 1, T...);
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template<class T> void chmin(T &a, T b) { if (a > b) a = b; }
template<class T> void chmax(T &a, T b) { if (a < b) a = b; }
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

// 平均， 上下界， 长度一样
// 相同项最少
// 差值最大为 2
// 两种策略
// 中间给两边，两边给中间，
void solve()
{
    int n;
    cin >> n;
    int ub = -inf;
    int lb = inf;
    vector<int> a(n + 1, 0);
    map<int, int> mp;
    // vector<int> cnt(MAXN, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        chmax(ub, a[i]);
        chmin(lb, a[i]);
        mp[a[i]]++;
        // cnt[a[i] + offset]++;
    }


    if(ub - lb == 0 || ub - lb == 1)
    {
        cout << n << "\n";
        for (int i = 1; i <= n;i++)
            cout << a[i] << " ";
        return;
    }

    vector<int> p, q;
    int l = mp[lb], m = mp[lb + 1], r = mp[lb + 2];
    int s1 = n - 2 * min(l, r), s2 = n - (m / 2) * 2;
    if(s1 < s2)
    {
        debug(s1);
        cout << s1 << "\n";
        for (int i = 0; i < l - min(l, r);i++)
            cout << lb << " ";
        
        for (int i = 0; i < r - min(l, r);i++)
            cout << lb + 2 << " ";

        for (int i = 0; i < m + 2 * min(l, r);i++)
            cout << lb + 1 << " ";
    }
    else
    {
        debug(s2);
        cout << s2 << "\n";
        for (int i = 0; i < l + m / 2;i++)
            cout << lb << " ";
        
        for (int i = 0; i < r + m / 2;i++)
            cout << lb + 2 << " ";

        for (int i = 0; i < m - (m / 2) * 2;i++)
            cout << lb + 1 << " ";
    }
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}