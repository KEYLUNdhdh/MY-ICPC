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
// bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

struct e
{
    i64 k, l, up, id;
};
void solve()
{
    int n, f;
    cin >> n >> f;

    vector<e> a(n + 1);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i].k >> a[i].l;
        a[i].id = i;
        // debug(a[i].k)
        if(a[i].k >= a[i].l)
            continue;
        i64 db = a[i].k * 2;
        a[i].up = min(db, a[i].l) - a[i].k;
    }

    sort(a.begin() + 1, a.end(), [](e p, e q){return p.up > q.up;});
    // for (int i = 1; i <= n;i++)
    // {
    //     cerr << a[i].k << " " << a[i].l << " " << a[i].id << " " << a[i].up << "\n";
    // }
    i64 ans = 0;
    for (int i = 1; i <= n;i++)
    {
        if(f > 0)
        {
            f--;
            ans += min(a[i].k * 2, a[i].l);
        }
        else
            ans += min(a[i].k, a[i].l);
        // debug(ans)debug(f)
    }

    cout << ans;
}
// bool ED;
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