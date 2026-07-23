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

// 非常好的从端点思考的方式，因为对于这题，如果端点已经确定了，整个的贡献就确定了。
// 所以考虑枚举端点情况。
// 这题比较特殊，我们要考虑 flip 的突变情况。
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(n - 1);
    for (int i = 0;i < n;i++)
        cin >> a[i];
    for (int i = 0; i < n - 1;i++)
        cin >> b[i];

    vector<int> c(n - 1);
    for (int i = 0; i < n - 1;i++)
        c[i] = (a[i] + a[i + 1]) % m;
    vector<int> up(n - 1);
    for (int i = 0; i < n - 1;i++)
        up[i] = (b[i] - c[i] + m) % m;


    debugarr(b)
    debugarr(c)
    debugarr(up)

    vector<int> p(n);
    p[n - 1] = 0;
    i64 cur = 0;
    vector<pll> snap;
    for (int i = n - 2; i >= 0;i--)
        p[i] = (up[i] - p[i + 1] + m) % m, cur += p[i];

    for (int i = 0; i < n;i++)
    {
        i64 dis = n - 1 - i;
        if(dis % 2 == 0)
        {
            i64 t = (m - p[i]) % m;
            if(t != 0)
                snap.emplace_back(t, -m);
        }
        else
        {
            i64 t = (p[i] + 1);
            if(t < m)
                snap.emplace_back(t, m);
        }   
    }

    sort(snap.begin(), snap.end());

    i64 lst = 0;
    i64 ans = cur;
    i64 sw = n % 2;
    // auto &[t, cost] : snap
    for (int i = 0; i < snap.size();)
    {
        i64 t = snap[i].first;
        cur += sw * (t - lst);
        int j = i + 1;
        cur += snap[i].second;
        while(j < snap.size() && snap[j].first == t)
            cur += snap[j].second, j++;

        chmin(ans, cur);
        lst = t;
        i = j;
    }

    cout << ans;
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