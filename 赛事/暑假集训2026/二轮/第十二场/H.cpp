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

struct BIT
{
    int n;
    vector<int> tree;
    BIT(){}
    BIT(int n_) : n(n_), tree(n + 1, -inf) {}
    void clear(int len)
    {
        n = len;
        tree.assign(len + 1, -inf);
    }

    void modify(int idx, int val)
    {
        for (int i = idx; i <= n;i += i & (-i))
        {
            tree[i] = max(tree[i], val);
        }
    }

    int query(int idx)
    {
        int res = -inf;
        for (int i = idx; i > 0;i -= i  & (-i))
            chmax(res, tree[i]);
        return res;
    }
};  

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<db> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    vector<db> p(n + 1, 0);
    vector<db> uni;

    auto id = [&](db k) -> int
    {
        return lower_bound(uni.begin(), uni.end(), k) - uni.begin() + 1;
    };

    BIT bit;
    auto check = [&](db x) -> int
    {
        p[0] = 0;
        for (int i = 1; i <= n;i++)
            p[i] = a[i] - x + p[i - 1];
        uni.assign(p.begin(), p.begin() + n + 1);
        sort(uni.begin(), uni.end());
        uni.erase(unique(uni.begin(), uni.end()), uni.end());
        int len = uni.size();
        bit.clear(len);
        vector<int> dp(n + 1, -inf);
        dp[0] = 0;
        bit.modify(id(p[0]), 0);
        for (int i = 1; i <= n;i++)
        {
            db curp = p[i];
            int idx = id(curp);
            int ans = bit.query(idx);
            if(ans > -inf / 2)
            {
                dp[i] = ans + 1;
                bit.modify(idx, dp[i]);
            }
        }
        return dp[n] >= k;
    };

    db l = 0, r = 1000;
    for (int i = 0; i < 50;i++)
    {
        db m = (l + r) / 2.;
        if(check(m))
            l = m;
        else
            r = m;
    }
    cout << fixed << setprecision(12) << l;
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