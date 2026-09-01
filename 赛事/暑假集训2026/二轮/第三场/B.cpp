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
    int n, k;
    cin >> n >> k;

    vector<vector<i64>> A(101), B(101);
    for (int i = 0; i < n;i++)
    {
        i64 a, b;
        cin >> a >> b;

        if(a <= 100)
            A[a].push_back(b);
        else
            B[b].push_back(a);
    }

    for (int i = 1; i <= 100;i++)
    {
        sort(A[i].rbegin(), A[i].rend());
        sort(B[i].rbegin(), B[i].rend());
    }
    vector<vector<i64>> dpa(6, vector<i64>(501, -1));
    vector<vector<i64>> dpb(6, vector<i64>(501, -1));
    dpa[0][0] = 0;
    dpb[0][0] = 0;

    for (int i = 1; i <= 100;i++)
    {
        for (int j = 0; j < k && j < A[i].size();j++)
        {
            i64 b = A[i][j];
            for (int c = 5; c >= 1;c--)
            {
                for (int x = c * 100; x >= i;x--)
                    if(dpa[c - 1][x - i] != -1)
                        chmax(dpa[c][x], dpa[c - 1][x - i] + b);
            }
        }
    }

    for (int i = 1; i <= 100;i++)
    {
        for (int j = 0; j < k && j < B[i].size();j++)
        {
            i64 a = B[i][j];
            for (int c = 5; c >= 1;c--)
            {
                for (int x = c * 100; x >= i;x--)
                    if(dpb[c - 1][x - i] != -1)
                        chmax(dpb[c][x], dpb[c - 1][x - i] + a);
            }
        }
    }

    i64 ans = 0;
    for (int ca = 0; ca <= k;ca++)
    {
        int cb = k - ca;
        for (int i = 0; i <= ca * 100;i++)
        {
            for (int j = 0; j <= cb * 100;j++)
            {
                i64 x = i, y = dpa[ca][i];
                i64 p = j, q = dpb[cb][j];
                if(y == -1 || q == -1)
                    continue;

                chmax(ans, (x + q) * (y + p));
            }
        }
    }
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