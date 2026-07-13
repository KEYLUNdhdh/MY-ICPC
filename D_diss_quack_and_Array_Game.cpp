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
constexpr i64 MOD = 998244353, INF = 2e18;
const int lim = 1e5 + 50;


vector<vector<i64>> best(32, vector<i64>(lim + 2, INF));
vector<vector<i64>> besto(32, vector<i64>(lim + 2, INF));
vector<int> c(lim + 1, 0);

void pre()
{
    c[1] = 1;
    for (int i = 1; i <= lim;i++)
    {
        if(i & 1)
            c[i] = c[i - 1] + 1;
        else
            c[i] = c[i / 2] + 1;
    }

    for (int t = 31; t >= 0;t--)
    {
        i64 mask = 1ll << t;
        best[t][lim + 1] = INF;
        besto[t][lim + 1] = INF;
        for (int i = lim - 1; i >= 1;i--)
        {
            best[t][i] = min(best[t][i + 1], mask * i + c[i]);
            besto[t][i] = besto[t][i + 1];
            if(i & 1)
                chmin(besto[t][i], mask * i + c[i]);
        }
    }
}

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n + 1, 0);
    int maxx = 0;
    i64 sum = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        chmax(maxx, a[i]);
        sum += a[i];
    }

    i64 ans = INF;
    for (int t = 31; t >= 0;t--)
    {
        i64 mask = 1ll << t;
        i64 tmp = 0;
        for (int i = 1; i <= n;i++)
        {
            i64 ld = (a[i] + mask - 1) / mask;
            tmp += best[t][ld];
        }
        tmp += t - sum;
        for (int i = 1; i <= n;i++)
        {
            i64 ld = (a[i] + mask - 1) / mask;
            chmin(ans, tmp + besto[t][ld] - best[t][ld]);
        }
    }
    cout << ans << "\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    pre();
    while(T--)
        solve();

    return 0;
}