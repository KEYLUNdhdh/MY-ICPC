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

struct EXKMP
{
    vector<int> z;
    vector<int> p;

    void get_z(const string& b)
    {
        int m = b.size();
        z.assign(m, 0);
        if(m == 0)
            return;
        z[0] = m;
        for (int i = 1, l = 0, r = -1; i < m;i++)
        {
            if(i <= r && z[i - l] < r - i + 1)
                z[i] = z[i - l];
            else
            {
                z[i] = max(0, r - i + 1);
                while(i + z[i] < m && b[z[i]] == b[i + z[i]])
                    z[i]++;
                
            }
            if(z[i] > r - i + 1)
            {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }

    void get_p(const string& a, const string& b)
    {
        int n = a.size(), m = b.size();
        p.assign(n, 0);
        for (int i = 0, l = 0, r = -1; i < n;i++)
        {
            if(i <= r && z[i - l] < r - i + 1)
                p[i] = z[i - l];
            else
            {
                p[i] = max(0, r - i + 1);
                while(i + p[i] < n && p[i] < m && a[i + p[i]] == b[p[i]])
                    p[i]++;
                
            }
            if(p[i] > r - i + 1)
            {
                l = i;
                r = i + p[i] - 1;
            }
        }
    }
};

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

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
    int n, l, r;
    cin >> n >> l >> r;

    string s;
    cin >> s;
    EXKMP kmp;
    kmp.get_z(s);
    const auto &z = kmp.z;

    DSU dsu(n);
    // 凑出长度为 x 的lcp，最多能切多少段
    vector<i64> cnt(n + 1, 0);
    for (int x = 1; x <= n;x++)
    {
        int cur = 0;
        while(cur < n)
        {
            while(cur < n && z[cur] < x)
            {
                // cur++;
                dsu.pretoSuf(cur, cur + 1);
                cur = dsu.find(cur);
            }

            if(cur >= n)
                break;

            cur = cur + x;
            cnt[x]++;
        }
    }

    debugarr(cnt);
    vector<i64> ans(n + 1, 0);
    for (int x = 1; x <= n;x++)
        chmax(ans[cnt[x]], (i64)x);

    for (int i = n - 1; i >= 1;i--)
        chmax(ans[i], ans[i + 1]);

    for (int i = l; i <= r;i++)
        cout << ans[i] << " ";
    cout << "\n";
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}