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
    string s;
    cin >> s;
    s = "*" + s;
    i64 ans = INF;
    vector<i64> cnt1(26, 0), cnt2(26, 0);
    for (int i = 1; i <= n;i++)
    {
        int idx = s[i] - 'a';
        if(i & 1)
            cnt1[idx]++;
        else
            cnt2[idx]++;
    }
    i64 maxx1 = 0, maxx2 = 0;
    for (int i = 0; i < 26;i++)
    {
        chmax(maxx1, cnt1[i]);
        chmax(maxx2, cnt2[i]);
    }

    vector<i64> suf1(26, 0), suf2(26, 0);
    int numo = n / 2, numji = n - numo;
    if(n % 2 == 0)
        chmin(ans, numo - maxx2 + numji - maxx1);
    else
    {
        debugarr(cnt1, cnt2);
        debug(ans);
        for (int i = n; i >= 1; i--)
        {
            int idx = s[i] - 'a';
            if(i & 1)
                cnt1[idx]--;
            else
                cnt2[idx]--;
            i64 mx1 = 0, mx2 = 0;
            for (int i = 0; i < 26;i++)
                chmax(mx1, cnt1[i] + suf2[i]);
            for (int i = 0; i < 26;i++)
                chmax(mx2, cnt2[i] + suf1[i]);
            debug(mx1, mx2);
            chmin(ans, numo - mx2 + numji - mx1);
            if(i & 1)
                suf1[idx]++;
            else
                suf2[idx]++;
            debugarr(cnt1, cnt2, suf1, suf2);
            debug(ans);
            cutline
        }
    }
    cutline
    cout << ans << "\n";
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