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

// 这里建的是权值线段树，val代表出现几次。
struct ChairmanTree
{
    struct Node
    {
        int ls, rs;
        int val;
    };

    int max_val;// 值域的 ub
    vector<Node> tr;
    vector<int> root;

    ChairmanTree(int M) : max_val(M)
    {
        tr.reserve(4000005);// N*log(N) 级别
        tr.push_back({0, 0, 0});
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
        tr[u].val++;

        if(l == r)
            return u;
        int mid = l + (r - l) / 2;
        if(pos <= mid)
            tr[u].ls = update(tr[prev_rt].ls, l, mid, pos);
        else
            tr[u].rs = update(tr[prev_rt].rs, mid + 1, r, pos);
        return u;
    }

    // v - u
    int query(int u, int v, int l, int r, int k)
    {
        if(l == r)
            return l;

        int lcnt = tr[tr[v].ls].val - tr[tr[u].ls].val;
        int mid = l + (r - l) / 2;
        if(k <= lcnt)
            return query(tr[u].ls, tr[v].ls, l, mid, k);
        else
            return query(tr[u].rs, tr[v].rs, mid + 1, r, k - lcnt);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1, 0);
    for(int i = 1; i <= n;i++)
        cin >> a[i];
    vector<int> uni = a;
    sort(uni.begin(), uni.end());
    uni.erase(unique(uni.begin(), uni.end()), uni.end());

    int MAX = uni.size() + 1;
    ChairmanTree cmt(MAX);
    for (int i = 1; i <= n;i++)
    {
        int val = lower_bound(uni.begin(), uni.end(), a[i]) - uni.begin() + 1;
        cmt.root.push_back(cmt.update(cmt.root.back(), 1, MAX, val));
    }

    while(m--)
    {
        int l, r, k;
        cin >> l >> r >> k;

        i64 val = cmt.query(cmt.root[l - 1], cmt.root[r], 1, MAX, k);

        cout << uni[val - 1] << "\n";
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