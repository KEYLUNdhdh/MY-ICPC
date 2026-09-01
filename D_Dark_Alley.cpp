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
constexpr i64 MOD = 1e9 + 7, INF = 2e18;
vector<i64> pr;
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
        // debug(res);
    }
    return res;
}

i64 inv(i64 a)
{
    return qpow(a, MOD - 2);
}

void precom(int n, i64 fac)
{
    pr.assign(n + 1, 0);
    pr[0] = 1;
    pr[1] = fac;
    for (int i = 2; i <= n;i++)
        pr[i] = pr[i - 1] * fac % MOD;
    debugarr(pr);
}

struct SegmentTree
{
    int n;
    vector<i64> suml, sumr;
    SegmentTree(int n_) : n(n_), suml(4 * n_ + 1, 0), sumr(4 * n_ + 1, 0) {}
    
    void pull(int p, int l, int r)
    {
        int m = l + r >> 1;
        int len = r - l + 1;
        // r - m - 1 + 1
        suml[p] = (suml[p << 1] + suml[p << 1 | 1] * pr[m - l + 1] % MOD) % MOD;
        sumr[p] = (sumr[p << 1] * pr[r - m] % MOD + sumr[p << 1 | 1]) % MOD;
    }

    void modify(int p, int l, int r, int pos, i64 val)
    {
        if(l == r)
        {
            suml[p] = ((suml[p] + val) % MOD + MOD) % MOD;
            sumr[p] = ((sumr[p] + val) % MOD + MOD) % MOD;
            return;
        }
        int m = l + r >> 1;
        if(pos <= m)
            modify(p << 1, l, m, pos, val);
        else
            modify(p << 1 | 1, m + 1, r, pos, val);
        pull(p, l, r);
    }

    void query(int p, int l, int r, int pos, i64 &ans)
    {
        if(l == r)
        {
            ans += suml[p];
            debug(l, r, ans, pos);

            return;
        }

        int m = l + r >> 1;
        debug(l, r, ans, pos);
        if(pos <= m)
        {
            ans = (ans + suml[p << 1 | 1] * pr[m - pos + 1] % MOD) % MOD;
            query(p << 1, l, m, pos, ans);
        }
        else
        {
            ans = (ans + sumr[p << 1] * pr[pos - m] % MOD) % MOD;
            query(p << 1 | 1, m + 1, r, pos, ans);
        }
    }
};



void solve()
{
    int n, q;
    string p;
    cin >> n >> q >> p;
    // debug(n, q, p);
    int pos = p.find('.');
    p = p.substr(pos + 1);
    int len = p.size();
    i64 den = 1;
    for (int i = 1; i <= len;i++)
        den *= 10;
    i64 num = stoi(p);
    i64 fac = (den - num) * inv(den) % MOD;
    // debug(p, num, den, den - num, fac, inv(den));
    precom(n, fac);

    SegmentTree seg(n);
    while(q--)
    {
        char op;
        cin >> op;
        if(op == '+')
        {
            i64 b;
            int x;
            cin >> b >> x;
            seg.modify(1, 1, n, x, b);
        }
        else if(op == '-')
        {
            i64 b;
            int x;
            cin >> b >> x;
            seg.modify(1, 1, n, x, -b);
        }
        else
        {
            int x;
            cin >> x;
            i64 ans = 0;
            seg.query(1, 1, n, x, ans);
            cout << ans % MOD << "\n";
        }
        cutline
    }
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    // precom();
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}