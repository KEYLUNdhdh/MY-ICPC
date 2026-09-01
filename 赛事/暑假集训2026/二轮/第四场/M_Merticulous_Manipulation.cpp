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

template<typename T>
struct Fenwick
{
    int n;
    vector<T> t1, t2;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        t1.assign(n + 1, T{});
        t2.assign(n + 1, T{});
    }

    void add(int x,T v)
    {
        T v2 = v * x;
        for (int i = x; i <= n;i += i & (-i))
        {
            t1[i] += v;
            t2[i] += v2;
        }
    }

    void rangeAdd(int l, int r, T v)
    {
        add(l, v);
        add(r + 1, -v);
    }

    T sum(int x)
    {
        T sum1{}, sum2{};
        for (int i = x; i > 0;i -= i & (-i))
        {
            sum1 += t1[i];
            sum2 += t2[i];
        }
        return sum1 * (x + 1) - sum2;
    }

    T rangeSum(int l,int r)
    {
        return sum(r) - sum(l - 1);
    }
    
};

void solve()
{
    int n;
    cin >> n;
    vector<i64> p(n + 1, 0);
    vector<int> pos(n + 1, 0);
    Fenwick<i64> bit(n);
    vector<i64> ans(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> p[i];
        pos[p[i]] = i;
        bit.rangeAdd(i, i, 1);
    }

    int s = 1;
    for (int m = n; m >= 1;m--)
    {
        int t = pos[m];
        int idx = 0;
        if(s <= t)
            idx = bit.rangeSum(s, t);
        else
            idx = bit.rangeSum(s, n) + bit.rangeSum(1, t);

        ans[m] = m - idx + 1;
        bit.rangeAdd(t, t, -1);
        s = (t % n) + 1;
        // assert(s == t);
    }

    for (int i = 1; i <= n;i++)
        cout << ans[i] << " ";
    cout << "\n";
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