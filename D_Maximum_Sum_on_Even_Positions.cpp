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

void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n);
    i64 sum = 0;
    
    // 强制使用 0-based 索引，直接贴合题意
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if(i % 2 == 0)
            sum += a[i]; // 加上真正的偶数项
    }

    // 情况 A: 翻转 [0, 1], [2, 3]... 这种偶数起点、奇数终点的区间
    i64 max_diff1 = 0, current_diff1 = 0;
    for (int i = 0; i + 1 < n; i += 2)
    {
        // 翻转后，失去了偶数位置的 a[i]，得到了奇数位置的 a[i+1]
        current_diff1 += a[i + 1] - a[i];
        if(current_diff1 < 0) current_diff1 = 0;
        chmax(max_diff1, current_diff1);
    }

    // 情况 B: 翻转 [1, 2], [3, 4]... 这种奇数起点、偶数终点的区间
    i64 max_diff2 = 0, current_diff2 = 0;
    for (int i = 1; i + 1 < n; i += 2)
    {
        // 翻转后，失去了偶数位置的 a[i+1]，得到了奇数位置的 a[i]
        current_diff2 += a[i] - a[i + 1];
        if(current_diff2 < 0) current_diff2 = 0;
        chmax(max_diff2, current_diff2);
    }

    // 最终答案 = 基础偶数和 + 两种合法翻转中的最大额外收益
    cout << sum + max({0LL, max_diff1, max_diff2}) << "\n";
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}