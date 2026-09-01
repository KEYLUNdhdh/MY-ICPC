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


#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SegmentTree
{
    struct Node
    {
        int ls, rs;
        i64 val;
        i64 lazy;
    };

    int n;
    vector<Node> tr;
    vector<int> root;

    SegmentTree(int n_, const vector<i64> &a) : n(n_)
    {
        // 预分配足够的空间：N + M * ceil(log2(N))
        root.assign(1e5, 0);
        tr.reserve(25000005);
        tr.push_back({0, 0, 0, 0});
        root[0] = build(1, n, a);
    }

    int cloneNode(int u)
    {
        tr.push_back(tr[u]);
        return tr.size() - 1;
    }

    // 1 - index
    int build(int l, int r, const vector<i64> &a)
    {
        int u = tr.size();
        tr.push_back({0, 0, 0});
        if(l == r)
        {
            tr[u].val = a[l];
            tr[u].lazy = 0;
            return u;
        }
        int mid = l + (r - l) / 2;
        tr[u].ls = build(l, mid, a);
        tr[u].rs = build(mid + 1, r, a);

        tr[u].val = tr[tr[u].ls].val + tr[tr[u].rs].val;
        tr[u].lazy = 0;
        return u;
    }

    int update(int prev_rt, int l, int r, int x, int y, i64 val)
    {
        if(l > y || r < x)
            return prev_rt;
        int u = cloneNode(prev_rt);
        
        if(l >= x && r <= y)
        {
            tr[u].val += val * (r - l + 1);
            tr[u].lazy += val;
            return u;
        }
        int mid = l + (r - l) / 2;
        tr[u].ls = update(tr[prev_rt].ls, l, mid, x, y, val);
        tr[u].rs = update(tr[prev_rt].rs, mid + 1, r, x, y, val);
        tr[u].val = tr[tr[u].ls].val + tr[tr[u].rs].val + tr[u].lazy * (r - l + 1);
        return u;
    }

    i64 query(int rt, int l, int r, int x, int y, i64 lazy)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return tr[rt].val + lazy * (r - l + 1);

        int mid = l + (r - l) / 2;
        return query(tr[rt].ls, l, mid, x, y, tr[rt].lazy + lazy) + query(tr[rt].rs, mid + 1, r, x, y, tr[rt].lazy + lazy);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    SegmentTree seg(n, a);
    int t = 0;
    while(m--)
    {
        char c;
        cin >> c;
        if(c == 'C')
        {
            int l, r;
            i64 d;
            cin >> l >> r >> d;
            seg.root[t + 1] = (seg.update(seg.root[t], 1, n, l, r, d));
            t++;    
        }
        else if(c == 'Q')
        {
            int l, r;
            cin >> l >> r;
            cout << seg.query(seg.root[t], 1, n, l, r, 0) << "\n";
        }
        else if(c == 'H')
        {
            int l, r, tt;
            cin >> l >> r >> tt;
            cout << seg.query(seg.root[tt], 1, n, l, r, 0) << "\n";
        }
        else
            cin >> t;
    }
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