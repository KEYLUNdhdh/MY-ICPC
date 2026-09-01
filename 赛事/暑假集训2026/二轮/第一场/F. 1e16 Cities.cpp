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
const i64 MAX = 1e16;

struct DSU
{
    vector<int> f, siz;
    int part;
    DSU() {};
    DSU(int n)
    {
        init(n);
    }
    //input n,open n + 1
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        part = n;
    }
    int find(int x)
    {
        while(x != f[x])
            x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(siz[x] < siz[y])
            swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        part--;
        return true;
    }
    //x -> y
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
    i64 a, b;
    cin >> a >> b;

    vector<i64> div;
    for (i64 i = 1; i * i <= b;i++)
    {
        if(b % i == 0)
        {
            div.push_back(i);
            if(i * i != b)
                div.push_back(b / i);
        }
    }

    vector<i64> nodes;
    vector<pll> edges;
    for(i64 k : div)
    {
        i64 s = a + b / k;
        i64 tmp = s;

        vector<i64> primes;
        for (int i = 2; i * i <= s;i++)
        {
            if(tmp % i == 0)
            {
                i64 pw = 1;
                while(tmp % i == 0)
                    tmp /= i, pw *= i;
                primes.push_back(pw);
            }
        }
        if(tmp > 1)
            primes.push_back(tmp);

        int m = primes.size();
        for (int msk = 0; msk < (1 << m);msk++)
        {
            i64 u = 1;
            for (int i = 0; i < m;i++)
            {
                if((1 << i) & msk)
                    u *= primes[i];
            }
            i64 v = s / u;
            i64 x = u * k;
            i64 y = v * k;
            if(x <= MAX && y <= MAX && x != y)
            {
                edges.push_back({x, y});
                nodes.push_back(x);
                nodes.push_back(y);
            }
        }
    }

    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    i64 V = nodes.size();
    vector<i64> xorsum(V, 0);
    for (int i = 0; i < V;i++)
        xorsum[i] = nodes[i];
    DSU dsu(V);
    for(auto &[x, y] : edges)
    {
        int xx = lower_bound(nodes.begin(), nodes.end(), x) - nodes.begin();
        int yy = lower_bound(nodes.begin(), nodes.end(), y) - nodes.begin();
        if(!dsu.same(xx, yy))
        {
            i64 fx = dsu.find(xx), fy = dsu.find(yy);
            dsu.pretoSuf(fx, fy);
            xorsum[fy] ^= xorsum[fx];
        }
    }

    int q;
    cin >> q;
    while(q--)
    {
        i64 k;
        cin >> k;
        auto it = lower_bound(nodes.begin(), nodes.end(), k) - nodes.begin();
        if(it >= V || nodes[it] != k)
        {
            cout << k << "\n";
        }
        else
        {
            i64 fk = dsu.find(it);
            cout << xorsum[fk] << "\n";
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
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}