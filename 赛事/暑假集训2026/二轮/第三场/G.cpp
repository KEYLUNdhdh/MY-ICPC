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
    vector<string> str;
    string tmp;
    while(getline(cin, tmp))
        str.push_back(tmp);
    i64 ans = 0;
    i64 maxx = 0;
    int len = str.size();
    vector<string> pre(len, "-1");
    for (int i = 0; i < str.size() - 1;)
    {
        string p = str[i];
        int pos = -1;
        if(p.find(',') == string::npos)
        {
            i++;
            continue;
        }
        else
            pos = p.find(',');
        debug(i, ans, maxx);
        string s = p.substr(0, pos);
        string cmp1 = s + ", " + s + " " + s + "ity " + s;
        string cmp2 = "i said " + s + ", " + s + " " + s + "ity " + s;
        if(cmp1 == str[i] && cmp2 == str[i + 1] && (i == 0 || s == pre[i - 1]))
        {
            maxx += 23 + 8 * s.size();
            pre[i] = pre[i + 1] = s;
            chmax(ans, maxx);
            i += 2;
        }
        else if(cmp1 == str[i] && cmp2 == str[i + 1])
        {
            maxx = 23 + 8 * s.size();
            pre[i] = pre[i + 1] = s;
            chmax(ans, maxx);
            i += 2;
        }
        else
        {
            maxx = 0;
            i++;
        }
    }
    if(ans == 0)
        cout << -1;
    else
        cout << ans;
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