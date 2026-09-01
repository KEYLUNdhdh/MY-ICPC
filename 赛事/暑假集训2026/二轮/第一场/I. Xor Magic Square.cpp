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

void solve()
{
    int n;
    cin >> n;
    if(n == 1 || n == 3)
    {
        cout << -1;
        return;
    }

    if(n % 2 == 0)
    {
        cout << n * n << "\n";
        for (int i = 1; i <= n;i++)
        {
            for (int j = 1;j <= n;j++)
            {
                cout << 1 << " ";
            }
            cout << "\n";
        }
        return;
    }
    else
    {
        vector<vector<int>> a = {
            {1, 1, 1, 2, 3},
            {2, 3, 1, 1, 1},
            {1, 1, 2, 3, 1},
            {3, 1, 1, 1, 2},
            {1, 2, 3, 1, 1}
        };

        i64 sum = n * n + 3 * n;
        vector<vector<int>> ans(n, vector<int>(n, 0));
        int m = n / 2 - 2;
        for (int i = 0; i < 5;i++)
            for (int j = 0; j < 5;j++)
                ans[i + m][j + m] = a[i][j];

        for (int i = 5 + m; i < n;i++)
        {
            ans[i][i] = ans[n - i - 1][n - i - 1] = 2;
            // debug(i, n - i - 1, ans[i][i])
            ans[i][n - i - 1] = ans[n - i - 1][i] = 3;
        }

        cout << sum << "\n";
        for (int i = 0; i < n;i++)
        {
            for (int j = 0; j < n;j++)
                if(ans[i][j] == 0)
                    cout << 1 << " ";
                else
                    cout << ans[i][j] << " ";
            cout << "\n";
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