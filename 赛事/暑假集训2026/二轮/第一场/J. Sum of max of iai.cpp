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
i64 p;
// i64 qpow(i64 a, i64 b)
// {
//     i64 res = 1;
//     a %= p;
//     while(b)
//     {
//         if(b & 1)
//             res = res * a % p;
//         a = a * a % p;
//         b >>= 1;
//     }
//     return res;
// }

// i64 inv(i64 a)
// {
//     return qpow(a, p - 2);
// }

vector<int> inv;
void invarr(int n)
{
    inv.assign(n + 5, 0);
    inv[1] = 1;
    for (int i = 2; i <= n;i++)
        inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    return;
}

void solve()
{
    i64 n;
    cin >> n >> p;

    invarr(n);
    i64 ans = n * n % p;
    for (int i = 2; i <= n;i++)
        ans = ans * i % p;

    i64 m = (n + 1) * (n + 1) / 4;

    vector<i64> a(n + 1, 0);
    i64 cura = 1;
    for (int i = 1; i <= n;i++)
    {
        i64 val = m / i - n + i;
        if(val > i)
            val = i;
        if(val < 0)
            val = 0;
        cura = cura * val % p;
    }


    vector<i64> delta(n * n + 1, 0);
    for (int i = m; i <= n * n - 1;i++)
        delta[i] = 1;

    for (int i = 1; i <= n;i++)
    {
        i64 k = m / i + 1;
        if(k <= n - i + 1)
            k = n - i + 2;

        for (int j = k; j <= n;j++)
        {
            i64 x = j * i;
            i64 val = j - n + i;
            i64 fac = val * inv[val - 1] % p;
            delta[x] = delta[x] * fac % p;
        }
    }

    i64 suma = 0;
    for (int x = m; x <= n * n;x++)
    {
        cura = cura * delta[x] % p;
        suma = (suma + cura) % p;
    }

    cout << ((ans - suma) % p + p) % p;
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