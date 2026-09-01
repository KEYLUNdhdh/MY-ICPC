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

template<typename T,typename F>
struct STable
{
    int n;
    int maxlog;
    vector<vector<T>> st;
    F func;
    //a 1 - index
    STable(const vector<T>& a,const F& f) : func(f)
    {
        n = a.size() - 1;
        maxlog = __lg(n) + 1;
        st.assign(n + 1, vector<T>(maxlog));
        for (int i = 1; i <= n;i++)
            st[i][0] = a[i];
        for (int j = 1; j < maxlog;j++)
        {
            int len = 1 << (j - 1);
            for (int i = 1;i <= n - (1 << j) + 1;i++)
                st[i][j] = func(st[i][j - 1], st[i + len][j - 1]);
        }
    }
    inline T query(int l,int r) const
    {
        if (l > r) 
            swap(l, r);
        int k = __lg(r - l + 1);
        return func(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n + 1, 0);
    vector<i64> premin(n + 1, INF), premax(n + 1, 0), sufmax(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        premin[i] = min(premin[i - 1], a[i]);
        premax[i] = max(premax[i - 1], a[i]);
    }

    sufmax[n] = a[n];
    for (int i = n - 1; i >= 1;i--)
        sufmax[i] = max(sufmax[i + 1], a[i]);

    STable st(a, [](i64 a, i64 b){return min(a, b);});
    debugarr(premax, sufmax, premin);
    for (int r = n - 1; r >= 2;r--)
    {
        i64 eq = sufmax[r + 1];
        debug(eq, r);
        auto xl = lower_bound(premax.begin() + 1, premax.end(), eq) - premax.begin();
        auto xr = upper_bound(premax.begin() + 1, premax.end(), eq) - premax.begin();
        xr--;
        if(xl >= r || xl > xr)
            continue;

        // 枚举第二个区间的左端点。

        debug(xl, xr);
        int le = xl;
        int ri = min<int>(xr + 2, r + 1);
        debug(le, ri);
        while(le + 1 < ri)
        {
            int m = le + ri >> 1;
            i64 num = st.query(m, r);
            debug(m, r, num);
            if(num <= eq)
                le = m;
            else
                ri = m;
        }
        if(le == xl)
            continue;
        i64 num = st.query(le, r);
        debug(le, num);

        if(num == eq)
        {
            debug(num, le);
            cout << "YES\n";
            int y = r - le + 1;
            int z = n - r;
            cout << le - 1 << " " << y << " " << z << "\n";
            return;
        }
        // for (int i = xl + 1; i <= xr + 1; i++)
        // {
        //     i64 num = st.query(i, r);
        //     if(num == eq)
        //     {
        //         debug(num, i);
        //         cout << "YES\n";
        //         int y = r - i + 1;
        //         int z = n - r;
        //         cout << i - 1 << " " << y << " " << z << "\n";
        //         return;
        //     }
        // }
        // auto xxl = lower_bound(premin.begin() + xl + 1, premin.end(), eq, greater<i64>()) - premin.begin();
        // auto xxr = upper_bound(premin.begin() + xl + 1, premin.end(), eq, greater<i64>()) - premin.begin();
        // xxr--;
        // debug(xxl, xxr);
        // if(xxl > r || xxl > xxr)
        //     continue;

        // debug(r, xl, xr, xxl, xxr);
        // i64 inter =  -max(xxl, xl) + min(xxr, xr) + 1;
        // if(inter >= 1)
        // {
        //     cout << "YES\n";
        //     int x = min(xxr, xr);
        //     int y = r - x;
        //     debug(x, r, y, n);
        //     cout << x << " " << y << " " << n - x - y << "\n";
        //     return;
        // }
    }
    cutline
    cout << "NO\n";
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