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

// 数组元素两两配对， / k 后总贡献最大
// 我们的总和其实是固定的
// 考虑模 k 的情况
// 我们让 a 和 a - k 配对，如果有这个一定是最优的。
// 如果没有呢? 我们应该考虑溢出最少的做法。
// 有个暴力，但感觉不是最优的
// 感觉暴力没毛啊
// 模拟加贪心加思维
void solve()
{
    int n, k;
    cin >> n >> k;
    i64 ans = 0;
    vector<i64> a(n + 1, 0);
    vector<int> cnt(k + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        ans += a[i] / k;
        a[i] %= k;
        cnt[a[i]]++;
    }

    debug(ans);
    debugarr(a, cnt);
    for (int i = 1; i <= k - 1;i++)
    {
        int l = i, r = k - i;
        int up;
        if(l != r)
            up = min(cnt[l], cnt[r]);
        else
            up = cnt[l] / 2;
        ans += up;
        cnt[l] -= up, cnt[r] -= up;
    }

    // for (int dis = 1;dis <= k )

    for (int i = 1; i < (k + 1) / 2; i++)
    {
        if (cnt[i] == 0)
            continue;
        int st = k - i + 1;
        for (int j = st; j <= k - 1;j++)
        {
            if(cnt[j] == 0)
                continue;

            int up = min(cnt[i], cnt[j]);
            cnt[i] -= up;
            cnt[j] -= up;
            ans += up;
        }
    }

    debugarr(cnt);
    int sum = 0;
    for (int i = (k + 1) / 2; i <= k - 1;i++)
        sum += cnt[i];
    ans += sum / 2;
    cout << ans << "\n";
    
    cutline
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