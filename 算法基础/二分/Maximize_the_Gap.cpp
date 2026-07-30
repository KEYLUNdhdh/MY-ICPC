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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    int k, n;
    cin >> n >> k;

    vector<pll> a(n + 1, {0, 0});
    for (int i = 1; i <= n;i++)
        cin >> a[i].first >> a[i].second;


    sort(a.begin() + 1, a.end(), [](pll p, pll q){return p.second < q.second;});

    auto check = [&](int x) -> bool
    {
        i64 prer = -INF;
        int cnt = 0;
        for (int i = 1; i <= n;i++)
        {
            if(prer + x <= a[i].first)
            {
                cnt++;
                prer = a[i].second;
            }
        }
        if(cnt >= k)
            return true;
        return false;
    };

    int l = -1, r = 1e9 + 1;
    while(l + 1 < r)
    {
        int m = l + r >> 1;
        if(check(m))
            l = m;
        else
            r = m;
    }

    if(l == 0)
        cout << -1;
    else
        cout << l;
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}