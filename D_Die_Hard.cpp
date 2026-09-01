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
    vector<array<i64, 6>> a(3);
    for (int i = 0; i < 3;i++)
        for (int j = 0; j < 6;j++)
            cin >> a[i][j];

    for (int i = 0; i < 3;i++)
    {
        int p, q;
        if(i == 0)
            p = 1, q = 2;
        else if(i == 1)
            p = 0, q = 2;
        else
            p = 0, q = 1;

        i64 cnt1 = 0, cnt2 = 0;
        int ava1 = 0, ava2 = 0;
        for (int x = 0; x < 6;x++)
        {
            for (int y = 0; y < 6;y++)
            {
                if(a[i][x] > a[p][y])
                    cnt1++;
                if(a[i][x] != a[p][y])
                    ava1++;
            }
        }

        for (int x = 0; x < 6;x++)
        {
            for (int y = 0; y < 6;y++)
            {
                if(a[i][x] > a[q][y])
                    cnt2++;
                if(a[i][x] != a[q][y])
                    ava2++;
            }
        }

        debug(cnt1, cnt2, ava1, ava2);
        debug(i, p, q);
        if(2 * cnt1 >= ava1  && (cnt1 != 0) && 2 * cnt2 >= ava2 && cnt2 != 0)
        {
            cout << i + 1;
            return;
        }
    }
    cout << "No dice";
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