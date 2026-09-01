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
    vector<i64> mulTag, addTag, sum, maxx;
    SegmentTree(int n_) : n{n_}, mulTag(4 * (n + 1) + 1, 1), addTag(4 * (n + 1) + 1, 0), sum(4 * (n + 1) + 1), maxx(4 * (n + 1) + 1, 0) {}

    void build(int p, int l, int r, const vector<i64> &a)
    {
        mulTag[p] = 1;
        addTag[p] = 0;
        if(l == r)
        {
            sum[p] = a[l];
            maxx[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        pull(p);
    }
    void pull(int p)
    {
        sum[p] = (sum[2 * p] + sum[2 * p + 1]);
        maxx[p] = max(maxx[p << 1], maxx[p << 1 | 1]);
    }
    void mul(int p,int v)
    {
        mulTag[p] = 1ll * mulTag[p] * v;
        addTag[p] = 1ll * addTag[p] * v;
        sum[p] = 1ll * sum[p] * v;
    }
    void push(int p,int l,int r)
    {
        if(mulTag[p] != 1)
        {
            mul(2 * p, mulTag[p]);
            mul(2 * p + 1,mulTag[p]);
            mulTag[p] = 1;
        }
        if(addTag[p] != 0)
        {
            int m = l + (r - l) / 2;
            applyAdd(2 * p, l, m, addTag[p]);
            applyAdd(2 * p + 1, m + 1, r, addTag[p]);
            addTag[p] = 0;
        }
    }
    i64 rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return -INF;
        if(l >= x && r <= y)
            return maxx[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return max(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m + 1, r, x, y));
    }
    i64 rangeQuery(int x,int y)
    {
        return rangeQuery(1, 0, n, x, y);
    }
    void rangeMul(int p,int l,int r,int x,int y,int v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
            return mul(p, v);
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeMul(2 * p, l, m, x, y, v);
        rangeMul(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeMul(int x,int y,int v)
    {
        rangeMul(1, 1, n, x, y, v);
    }
    void applyAdd(int p,int l,int r,int v)
    {
        addTag[p] = (1ll * addTag[p] + 1ll * v);
        sum[p] = (1ll * sum[p] + 1ll * (r - l + 1) * v);
        maxx[p] += v;
    }
    void rangeAdd(int p,int l,int r,int x,int y,int v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applyAdd(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeAdd(int x,int y,int v)
    {
        rangeAdd(1, 0, n, x, y, v);
    }
};


void solve()
{
    int n, k;
    cin >> n >> k;
    vector<i64> a;
    vector<pll> e(n);
    for (int i = 0; i < n;i++)
    {
        cin >> e[i].first >> e[i].second;
        a.push_back(e[i].first);
        a.push_back(e[i].second);
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int M = a.size();
    vector<vector<int>> add(M + 2), del(M + 2);

    for(auto &[l, r] : e)
    {
        int ll = lower_bound(a.begin(), a.end(), l) - a.begin() + 1;
        int rr = lower_bound(a.begin(), a.end(), r) - a.begin() + 1;
        add[ll].push_back(ll);
        del[rr].push_back(ll);
    }

    vector<i64> dp(M + 1, -INF);
    vector<i64> ndp(M + 1, -INF);
    dp[0] = 0;
    SegmentTree seg(M);
    i64 ans = 0;
    for (int i = 1; i <= k;i++)
    {
        ndp.assign(M + 1, -INF);
        seg.build(1, 0, M, dp);
        for (int j = 1; j <= M;j++)
        {
            for (int l : add[j])
                seg.rangeAdd(0, l - 1, 1);

            ndp[j] = seg.rangeQuery(0, j - 1);
            chmax(ans, ndp[j]);

            for (int l : del[j])
                seg.rangeAdd(0, l - 1, -1);
        }
        dp = ndp;
    }
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