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
const int MAX = 1e4 + 5;
const int N = 5050;
int f[N][N];
int deal(vector<int> b, vector<int> a)
{
    int n = a.size();
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int len = 1; len <= n; ++len)
    {
        for (int l = 0; l + len - 1 < n; ++l)
        {
            int r = l + len - 1;
            int cur = b[len - 1];
            f[l][r] = max(f[l + 1][r] + (a[l] > cur), f[l][r - 1] + (a[r] > cur));
        }
    }
    return f[0][n - 1];
}

void solve()
{
    int n;
    cin >> n;

    vector<pii> a(n);
    vector<int> b(n), oria(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
        oria[i] = a[i].first;
        a[i].second = i;
    }
    for (int i = 0; i < n; i++)
        cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());

    vector<int> ca(MAX, 0), cb(MAX, 0);
    for (int i = 0; i < n; i++)
        ca[oria[i]]++;
    for (int i = 0; i < n; i++)
        cb[b[i]]++;
    // int needwin = 0;
    // int cura = 0;
    // for (int i = 1; i <= 10000;i++)
    // {
    //     needwin += min(cura, cb[i]);
    //     cura = max(0, cura - cb[i]);
    //     cura += ca[i];
    // }
    int needwin = deal(oria, b);
    auto checkwin = [&](int x) -> bool
    {
        cb[x]--;
        int cura = 0;
        int win = 0;
        for (int i = 1; i <= 10000; i++)
        {
            win += min(cura, cb[i]);
            cura = max(0, cura - cb[i]);
            cura += ca[i];
        }
        cb[x]++;
        return win >= needwin - 1;
    };

    auto checklose = [&](int x) -> bool
    {
        cb[x]--;
        int cura = 0;
        int win = 0;
        for (int i = 1; i <= 10000; i++)
        {
            win += min(cura, cb[i]);
            cura = max(0, cura - cb[i]);
            cura += ca[i];
        }
        cb[x]++;
        return win >= needwin;
    };

    for (int i = 0; i < n; i++)
    {
        int p = oria[i];
        ca[p]--;
        vector<int> cur;
        for (int i = 1; i <= 10000; i++)
            if (cb[i])
                cur.push_back(i);

        int oril = upper_bound(cur.begin(), cur.end(), p) - cur.begin() - 1;
        int l = oril;
        int r = cur.size();
        while (l + 1 < r)
        {
            int m = l + r >> 1;
            int x = cur[m];
            if (checkwin(x))
                l = m;
            else
                r = m;
        }
        if (l != oril)
        {
            cout << cur[l] << " ";
            cb[cur[l]]--;
            needwin--;
        }
        else
        {
            l = -1;
            r = oril + 1;
            while (l + 1 < r)
            {
                int m = l + r >> 1;
                int x = cur[m];
                if (checklose(x))
                    l = m;
                else
                    r = m;
            }
            cout << cur[l] << " ";
            cb[cur[l]]--;
        }
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