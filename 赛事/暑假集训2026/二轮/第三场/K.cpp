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

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

i64 inv(i64 a)
{
    return qpow(a, MOD - 2);
}

struct ChairmanTree
{
    struct Node
    {
        int ls, rs;
        int cnt;
        i64 cost;
        i64 prod;
    };

    int max_val;// 值域的 ub
    vector<Node> tr;
    vector<int> root;
    vector<i64> vals;

    ChairmanTree(int M, const vector<i64> &v) : max_val(M), vals(v)
    {
        tr.reserve(4000005);// N*log(N) 级别
        tr.push_back({0, 0, 0, 0, 1});
        root.push_back(0);
    }

    int cloneNode(int u)
    {
        tr.push_back(tr[u]);
        return tr.size() - 1;
    }

    int update(int prev_rt, int l, int r, int pos)
    {
        int u = cloneNode(prev_rt);

        if(l == r)
        {
            tr[u].cnt++;
            tr[u].cost += vals[l - 1] - 1;
            tr[u].prod = tr[u].prod * vals[l - 1] % MOD;
            return u;
        }
        int mid = l + (r - l) / 2;
        if(pos <= mid)
            tr[u].ls = update(tr[prev_rt].ls, l, mid, pos);
        else
            tr[u].rs = update(tr[prev_rt].rs, mid + 1, r, pos);

        tr[u].cnt = tr[tr[u].ls].cnt + tr[tr[u].rs].cnt;
        tr[u].cost = tr[tr[u].ls].cost + tr[tr[u].rs].cost;
        tr[u].prod = tr[tr[u].ls].prod * tr[tr[u].rs].prod % MOD;
        return u;
    }

    // v - u
    int query(int u, int v, int l, int r, i64 k)
    {
        if(l == r)
        {
            i64 val = vals[l - 1];
            if(val == 1)
                return 1;
            i64 c = tr[v].cnt - tr[u].cnt;
            if(c == 0)
                return 1;

            i64 full = k / (val - 1);
            i64 rem = k % (val - 1);
            i64 steady = c - full - 1;
            i64 res = qpow(val, steady);
            res = res * (val - rem) % MOD;
            return res;
        }

        int mid = l + (r - l) / 2;
        i64 lc = tr[tr[v].ls].cost - tr[tr[u].ls].cost;
        if(k >= lc)
            return query(tr[u].rs, tr[v].rs, mid + 1, r, k - lc);
        else
        {
            i64 rprodu = tr[tr[u].rs].prod;
            i64 rprodv = tr[tr[v].rs].prod;
            i64 rprod = rprodv * inv(rprodu) % MOD;
            i64 lres = query(tr[u].ls, tr[v].ls, l, mid, k);
            return lres * rprod % MOD;
        }
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    vector<i64> uni = a;
    sort(uni.begin(), uni.end());
    uni.erase(unique(uni.begin(), uni.end()), uni.end());

    int M = uni.size();
    ChairmanTree cmt(M, uni);
    for (int i = 1; i <= n;i++)
    {
        i64 v = lower_bound(uni.begin(), uni.end(), a[i]) - uni.begin() + 1;
        cmt.root.push_back(cmt.update(cmt.root.back(), 1, M, v));
    }

    auto &tr = cmt.tr;
    auto &root = cmt.root;
    while(q--)
    {
        int l, r;
        i64 k;
        cin >> l >> r >> k;

        i64 total = tr[root[r]].cost - tr[root[l - 1]].cost;
        if(total <= k)
            cout << 1 << "\n";
        else
            cout << cmt.query(root[l - 1], root[r], 1, M, k) << "\n";
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