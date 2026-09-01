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

    vector<int> p(n + 1, 0), in(n + 1, 0), de(n + 1, 0);
    in[n] = 1, de[n] = 1, p[n] = 1;
    for (int i = n - 1; i >= 1; i--)
    {
        if (a[i] <= a[i + 1])
            in[i] = in[i + 1] + 1;
        else
            in[i] = 1;

        if (a[i] > a[i + 1])
            de[i] = de[i + 1] + 1;
        else
            de[i] = 1;
        p[i] = max(in[i], de[i]);
    }
    debugarr(in, de, p);
    vector<pll> ans(n + 1, {-1, -1});
    for (int minrun = 1; minrun <= 100 && minrun <= n; minrun++)
    {
        int cur = 1;
        int bad = 0;
        int seg = 0;
        while (cur <= n)
        {
            // int step = p[cur
            int curlen = p[cur];
            debug(curlen, minrun, cur, bad);
            int minn = min(minrun, n - cur + 1);
            if (curlen < minn)
                bad += minn - curlen, curlen = minn;
            cur = cur + curlen;
            seg++;
            debug(curlen, minrun, cur, bad);
            cutline
        }
        ans[minrun].first = seg, ans[minrun].second = bad;
        cutline cutline
    }

    int q;
    cin >> q;
    while (q--)
    {
        int m;
        cin >> m;
        if (ans[m].first != -1)
        {
            cout << ans[m].first << " " << ans[m].second << "\n";
            continue;
        }
        int cur = 1;
        int bad = 0;
        int seg = 0;
        while (cur <= n)
        {
            // int step = p[cur
            int curlen = p[cur];
            debug(curlen, m, cur, bad);
            int minn = min(m, n - cur + 1);
            if (curlen < minn)
                bad += minn - curlen, curlen = minn;
            cur = cur + curlen;
            seg++;
            debug(curlen, m, cur, bad);
            cutline
        }
        ans[m].first = seg, ans[m].second = bad;
        cout << ans[m].first << " " << ans[m].second << "\n";
    }
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}