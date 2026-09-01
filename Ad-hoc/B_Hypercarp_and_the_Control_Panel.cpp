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
void debug_out(Head H, Tail... T)
{
    cerr << " " << H;
    debug_out(T...);
}
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char *names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char *names, Head H, Tail... T)
{
    while (*names == ' ' || *names == ',')
        names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i)
    {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[')
            bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']')
            bracket--;
        else if (names[i] == ',' && bracket == 0)
            break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H)
        cerr << v << " ";
    cerr << "\n";

    debugarr_out(names + i + 1, T...);
}
#define cutline                             \
    {                                       \
        cerr << "----------------------\n"; \
    }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template <class T>
void chmin(T &a, T b)
{
    if (a > b)
        a = b;
}
template <class T>
void chmax(T &a, T b)
{
    if (a < b)
        a = b;
}
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    if (n == 1)
    {
        cout << 1 << "\n";
        return;
    }
    else if (n == 1)
    {
        if (a[1] != a[2])
            cout << 2 << "\n";
        else
            cout << 1 << "\n";
        return;
    }

    vector<pii> b;
    int i = 1;
    while (i <= n)
    {
        int cur = a[i];
        int cnt = 1;
        while (i < n && a[i] == a[i + 1])
        {
            cnt++;
            i++;
        }
        b.push_back({cur, cnt});
        i++;
    }
    for (auto &[val, c] : b)
        cerr << val << " " << c << "\n";
    cutline

        int ans = b.size();
    if (ans == n)
    {
        cout << ans << "\n";
        return;
    }

    int res = ans;
    debug(ans);
    for (int i = 0; i < b.size(); i++)
    {
        if (i < b.size() - 1 && b[i].second >= 2 && b[i + 1].second >= 2)
        {
            chmax(res, ans + 2);
            break;
        }
        else if (b[i].second >= 2)
        {
            if (i == 1)
            {
                chmax(res, ans + 1);
            }
            else if (i == (int)b.size() - 2)
            {
                chmax(res, ans + 1);
            }
            else
            {
                int p = i - 2;
                int n = i + 2;
                if (p >= 0 && b[i].first != b[p].first)
                    chmax(res, ans + 1);
                else if (n < b.size() && b[i].first != b[n].first)
                    chmax(res, ans + 1);
            }
        }
    }
    cout << res << "\n";
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}