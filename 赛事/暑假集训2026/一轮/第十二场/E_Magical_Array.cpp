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

// 前缀和吗
//  普通数组 p[i - 1]++, p[j]--;
// special array p[i - 1]++, p[j]--, p[j + 1]--;
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<i64>> a(n + 1, vector<i64>(m + 1, 0));
    vector<vector<i64>> p(n + 1, vector<i64>(m + 1, 0));

    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            cin >> a[i][j];
            p[i][j] = a[i][j] + p[i][j - 1];
        }
    }

    map<i64, int> mp;
    i64 sum1 = 0, sum2 = 0;
    int possum2 = -1;
    for (int i = 1; i <= m;i++)
        sum1 += p[1][i];
    mp[sum1]++;
    for (int i = 2; i <= n; i++)
    {
        i64 tmpsum = 0;
        for (int j = 1; j <= m; j++)
            tmpsum += p[i][j];
        if(tmpsum != sum1)
            sum2 = tmpsum, possum2 = i;
        mp[tmpsum]++;
    }

    debug(sum1, mp[sum1]);
    debug(sum2, mp[sum2]);

    if(mp[sum1] == 1)
    {
        int op = sum2 - sum1;
        cout << 1 << " " << op << "\n";
    }
    else
    {
        int op = sum1 - sum2;
        cout << possum2 << " " << op << "\n";
    }
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