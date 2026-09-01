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


// 不能这么配对啊
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> cnt(m + 1, 0), l(m + 1, 0), r(m + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        int c;
        cin >> c;
        cnt[c] += 2;
        l[c]++, r[c]++;
    }

    int ans = n;
    vector<pii> p(n + 1, {0, 0});
    for (int i = 1; i <= m;i++)
    {
        int up = cnt[i] - n;
        if(up > 0)
            ans -= up;

    }

    int idx = 1;
    for (int i = 1; i <= n;i++)
    {
        while(l[idx] == 0)
            idx++;

        p[i].first = idx;
        l[idx]--;
    }

    debug(idx);
    idx = 1;
    for (int i = 1; i <= n;i++)
    {
        while(r[idx] == 0)
            idx++;

        int cur = (i - 1 + n / 2) % n + 1;
        p[cur].second = idx;
        r[idx]--;
    }


    cout << ans << "\n";
    // debug(ans);
    for (int i = 1; i <= n;i++)
    {
        // int f = p[i].first, s = p[i].second;
        // debug(p[i].first, p[i].second);
        // debug(l[p[i].first], r[p[i].second]);
        // if (l[f] == 0)
        //     swap(p[i].first, p[i].second);
        // else if(r[s] == 0)
        //     swap(p[i].first, p[i].second);
        cout << p[i].first << " " << p[i].second << "\n";
        debug(p[i].first, p[i].second);
        
        // l[p[i].first]--, r[p[i].second]--;
        debug(l[p[i].first], r[p[i].second]);
        cutline

    }
    return;
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