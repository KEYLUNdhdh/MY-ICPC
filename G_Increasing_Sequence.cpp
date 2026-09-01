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

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    i64 k;
    cin >> n >> k;
    vector<i64> a(n + 1, 0);
    vector<i64> num(64, -1);
    int st = 0;
    int pos = __lg(k);
    // debug(pos, k);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    if(k == 0)
    {
        if(is_sorted(a.begin() + 1, a.end()))
            cout << 1 << "\n";
        else
            cout << 0 << "\n";
        return;
    }
    // debugarr(a);
    // 010
    // 101
    for (int i = 1; i < n; i++)
    {
        i64 cur = a[i], nx = a[i + 1];
        debug(i);
        for (int j = 63; j >= 0; j--)
        {
            i64 pc = (1ll << j) & cur;
            i64 pn = (1ll << j) & nx;
            if (!pc && pn)
            {
                if (num[j] == 1)
                {
                    cout << 0 << "\n";
                    return;
                }
                num[j] = 0, st++;
                break;
            }
            else if (pc && !pn)
            {
                if (num[j] == 0 || j > pos)
                {
                    cout << 0 << "\n";
                    return;
                }
                num[j] = 1, st++;
                break;
            }
        }
    }
    debugarr(a);

    // for(int i =)
    i64 ans = 0;
    vector<int> free(64, 0);
    free[0] = 0;
    for (int i = 1; i < 64; i++)
        free[i] = free[i - 1] + (num[i - 1] == -1 ? 1 : 0);

    debugarr(num);
    // debug(free, pos);
    int ok = 1;
    for (int i = 62; i >= 0; i--)
    {
        i64 p = (1ll << i) & k;
        if (num[i] == -1)
        {
            // debug(i, p);
            if (p)
                ans += qpow(2, free[i]);
            // debug(ans);
            // free--;
        }
        else
        {
            if (p && num[i] == 0)
            {
                ans += qpow(2, free[i]);
                ok = 0;
                // debug(ans);
                break;
            }
            else if (p && num[i] == 1)
            {
                // free--;
                continue;
            }
            else if (!p && num[i] == 0)
            {
                // free--;
                continue;
            }
            else if (!p && num[i] == 1)
            {
                ok = 0;
                break;
            }
        }
        // debug(i, free);
    }
    if(ok)
        ans++;
    cout << ans << "\n";
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