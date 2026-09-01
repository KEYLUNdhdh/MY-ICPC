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


// 8 2
// 16 3
// 32 3
// 64 4
// 128 4
// 256 5
// 512 5
void solve()
{
    int n, k;
    cin >> n >> k;
   
    vector<i64> F(17, 0);
    for (int i = 2; i <= 16;i++)
        F[i] = 4ll * (i - 1) * ((1ll << i) - 1);

    while(n--)
    {
        i64 h;
        cin >> h;
        if(h % 4 != 0 || h > F[k])
        {
            cout << -1 << "\n";
            continue;
        }

        vector<i64> ans;
        int r = k;
        while(h > 0)
        {
            if(h <= F[r - 1])
            {
                r--;
                continue;
            }
            i64 need = h - F[r - 1];
            bool ok = 0;
            for (int j = 0; j <= r - 1;j++)
            {
                i64 v = (1ll << (j + 2));
                i64 lb = 1ll * j * v;
                i64 ub;
                if(j + 2 <= r)
                    ub = 1ll * (j + 1) * v;
                else
                    ub = 1ll * (j + 1) * v - 4;
                i64 c = max(lb, need);
                if(c == 0)
                    c = 4;

                if(c <= ub && c <= h)
                {
                    ans.push_back(v);
                    h -= c;
                    r--;
                    ok = 1;
                    break;
                }
            }
            assert(ok);
        }
        cout << ans.size() << " ";
        for(i64 x : ans)
            cout << x << " ";
        cout << "\n";
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