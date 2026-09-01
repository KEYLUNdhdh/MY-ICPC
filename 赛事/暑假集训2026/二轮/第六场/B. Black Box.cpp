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

struct SegmentTree
{
    int n;
    vector<i64> val;
    SegmentTree(int n_) : n(n_), val(4 * (n + 1) + 1, 0) {}

    void insert(int x, int p, int l, int r, int v)
    {
        if (l == r)
        {
            val[p] += v;
            return;
        }
        int m = l + r >> 1;
        if(x <= m)
            insert(x, p << 1, l, m, v);
        else
            insert(x, p << 1 | 1, m + 1, r, v);
        val[p] = val[p << 1] + val[p << 1 | 1];
    }

    int query(int p, int l, int r, int x, int y)
    {
        if(l > y || r  < x)
            return 0;
        if(l >= x && r <= y)
        {
            return val[p];
        }

        int m = l + r >> 1;
        return query(p << 1, l, m, x, y) + query(p << 1 | 1, m + 1, r, x, y);
    }

    int querypos(int p, int l, int r, int k)
    {
        if(l == r)
            return l;
        int m = l + r >> 1;
        int lhs = p << 1;
        if(k < val[lhs])
            return querypos(lhs, l, m, k);
        else
            return querypos(p << 1 | 1, m + 1, r, k - val[lhs]);
    }

};
void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n);
    for (int i = 0; i < n;i++)
        cin >> a[i];

    i64 pos = a[n - 1] % (n - 1);
    swap(a[0], a[pos]);
    SegmentTree seg(n);
    for (int i = 0; i < n;i++)
        seg.insert(i, 1, 0, n - 1, 1);
    
    int idx = 0, len = n;
    vector<int> ans(n);
    for(int val : a)
    {
        i64 vv = seg.querypos(1, 0, n - 1, idx);
        debug(vv);
        seg.insert(vv, 1, 0, n - 1, -1);
        ans[vv] = val;
        len--;
        if(len)
            idx = (idx + val + len - 1) % len;
    }
    for (int i = 0; i < n;i++)
        cout << ans[i] << "\n";
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