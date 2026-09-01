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

vector<vector<int>> lines = { {0, 1, 2}, {3, 4, 5, 6}, {7, 8, 9, 10, 11}, {12, 13, 14, 15}, {16, 17, 18}, {7, 12, 16}, {3, 8, 13, 17}, {0, 4, 9, 14, 18}, {1, 5, 10, 15}, {2, 6, 11}, {0, 3, 7}, {1, 4, 8, 12}, {2, 5, 9, 13, 16}, {6, 10, 14, 17}, {11, 15, 18} };

vector<i64> valid;
const int MAXN = (1 << 19);
void solve()
{

    for(auto &line : lines)
    {
        // i64 mask = 0;
        int len = line.size();
        for (int i = 0; i < len;i++)
        {
            i64 mask = 0;
            for (int j = i; j < len;j++)
            {
                mask |= (1ll << line[j]);
                valid.push_back(mask);
            }
        }
    }

    sort(valid.begin(), valid.end());
    valid.erase(unique(valid.begin(), valid.end()), valid.end());

    vector<int> memo(MAXN + 5, -1);

    i64 cur = 0;
    char c;
    for (int i = 0; i < 19;i++)
    {
        cin >> c;
        debug(c);
        if(c == 'O')
            cur |= (1 << i);
    }

    debug(cur);
    auto dfs = [&](auto self, i64 state) -> int
    {
        if (state == 0)
            return 0;
        if (memo[state] != -1)
            return memo[state];

        for (i64 move : valid)
        {
            if ((state & move) == move)
            {
                i64 nx = state ^ move;
                int f = self(self, nx);
                if (f == 0)
                    return memo[state] = 1;
            }
        }
        return memo[state] = 0;
    };

    int ans = dfs(dfs, cur);
    if(ans)
        cout << "Karlsson";
    else
        cout << "Lillebror";
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