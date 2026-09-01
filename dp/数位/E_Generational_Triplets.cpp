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

i64 memo[65][2][2][2];
int vis[65][2][2][2];
int id = 0;

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

void solve()
{
    i64 n;
    cin >> n;
    vector<int> dig;
    i64 tmp = n;
    while(tmp)
    {
        dig.push_back(tmp % 2);
        tmp /= 2;
    }
    id++;
    
    auto dfs = [&](auto self, int pos, int la, int lc, int req) -> i64
    {
        if(pos < 0)
            return req == 0 ? 1 : 0;

        if(vis[pos][la][lc][req] == id)
            return memo[pos][la][lc][req];
        int uba = la ? dig[pos] : 1;
        int ubc = lc ? dig[pos] : 1;
        i64 res = 0;
        for (int a = 0; a <= uba;a++)
            for (int c = 0; c <= ubc;c++)
            {
                if((a & c) == req)
                {
                    int nreq = a ^ c;
                    res = (res + self(self, pos - 1, la && (a == uba), lc && (c == ubc), nreq)) % MOD;
                }
            }
        vis[pos][la][lc][req] = id;
        return memo[pos][la][lc][req] = res;
    };

    i64 m = dfs(dfs, dig.size() - 1, 1, 1, 0);
    i64 ans = (m - 1 + MOD) % MOD;
    ans = ans * inv(2) % MOD;
    cout << ans << "\n";
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