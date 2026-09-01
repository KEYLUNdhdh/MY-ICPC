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

struct DSU
{
    vector<int> f, siz;
    int part;
    DSU() {};
    DSU(int n)
    {
        init(n);
    }
    // input n,open n + 1
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        part = n;
    }
    int find(int x)
    {
        while (x != f[x])
            x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (siz[x] < siz[y])
            swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        part--;
        return true;
    }
    // x -> y
    void pretoSuf(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        f[x] = y;
        siz[y] += siz[x];
        part--;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1), revadj(n + 1);
    vector<pii> e;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        revadj[v].push_back(u);
        adj[u].push_back(v);
        e.push_back({u, v});
    }

    vector<int> tag1(n + 1, 0), tag2(n + 1, 0);
    queue<int> q;
    tag1[1] = 1, tag2[n] = 1;
    q.push(1);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v : adj[u])
        {
            if(!tag1[v])
            {
                tag1[v] = 1;
                q.push(v);
            }
        }
    }

    q.push(n);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : revadj[u])
        {
            if (!tag2[v])
            {
                tag2[v] = 1;
                q.push(v);
            }
        }
    }

    if(!tag1[n])
    {
        cout << 0 << "\n";
        return;
    }

    int ee = 0, v = 0;
    for (int i = 1; i <= n;i++)
        if(tag1[i] && tag2[i])
            tag1[i] = 1, v++;
        else
            tag1[i] = 0;

    for (int i = 0; i < e.size();i++)
    {
        auto &[u, v] = e[i];
        if(tag1[u] && tag1[v])
            ee++;
    }
    cout << ee - v + 2 << "\n";
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