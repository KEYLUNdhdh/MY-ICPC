#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    int n, q;
    cin >> n >> q;

    
    vector<i64> a(n);
    map<int, int> mp;
    for (int i = 0; i < n;i++)
        cin >> a[i], mp[a[i]] = 1;

    sort(a.begin(), a.end());

    // debugarr(a)
    auto check = [&](int idx, int m, int x, int y) -> bool
    {
        // debug(idx)
        int pos = upper_bound(a.begin(), a.end(), m) - a.begin();
        // debug(pos)
        int del = pos - idx;
        int res = m - x + 1 - del;
        return res < y;
    };

    while(q--)
    {
        i64 x, y;
        cin >> x >> y;

        int idx = lower_bound(a.begin(), a.end(), x) - a.begin();
        i64 l = x - 1, r = 2e9 + 1;
        while(l + 1 < r)
        {
            i64 m = l + r >> 1;
            if(check(idx, m, x, y))
                l = m;
            else
                r = m;

            // debug(l)debug(r)debug(m)
            // cutline
        }
        cout << r << "\n";
    }
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}