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

// 大二分？
// 不能枚举
// 可以枚举
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<pii> mem(m + 1, {0, 0});
    for (int i = 1; i <= m;i++)
        cin >> mem[i].first >> mem[i].second;

    // sort(mem.begin() + 1, mem.end());
    i64 ans = 0;
    auto &[a, b] = mem[1];
    int fa = 1;

    set<pii> st;
    auto check = [&](int x, int y) -> bool
    {
        cutline
        debug(x, y);
        for (int i = 1; i <= m;i++)
        {
            auto &[p, q] = mem[i];
            debug(p, q);
            if(p == x || q == x || p == y || q == y)
                continue;
            return false;
        }
        debug(x, y);
        return true;
    };
    // a
    for (int j = 2; j <= m;j++)
    {
        auto &[p, q] = mem[j];
        if(p == a || q == a)
            continue;

        fa = 0;
        if(check(a, p))
        {
            if(a > p)
                st.insert({p, a});
            else
                st.insert({a, p});
        }
        if(check(a, q))
        {
            if(a > q)
                st.insert({q, a});
            else
                st.insert({a, q});
        }
        break;
    }
    if(fa == 1)
        ans += n - 1;
    // b

    int fb = 1;
    for (int j = 2; j <= m;j++)
    {
        auto &[p, q] = mem[j];
        if(p == b || q == b)
            continue;

        fb = 0;
        if(check(b, p))
        {
            if(b > p)
                st.insert({p, b});
            else
                st.insert({b, p});
        }
        if(check(b, q))
        {
            if(b > q)
                st.insert({q, b});
            else
                st.insert({b, q});
        }
        break;
    }

    if(fb && fa)
        ans += n - 2;
    else if(fb)
        ans += n - 1;
    debug(ans);
    if(fa && fb)
    {
        cout << ans << "\n";
    }
    else if(fa || fb)
    {
        cout << ans + st.size() - 1 << "\n";
    }
    else
        cout << st.size() << "\n";
    // for(auto &[p, q] : st)
    //     cerr << p << " " << q << "\n";
    // cout << ans + st.size();
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