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
    int n, c;
    cin >> n >> c;

    vector<int> a(n), b(n);
    i64 suma = 0, sumb = 0;
    int mina = INF, minb = INF;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        suma += a[i];
        chmin(mina, a[i]);
    }

    for (int i = 0; i < n;i++)
    {
        cin >> b[i];
        sumb += b[i];
        chmin(minb, b[i]);
    }

    if((suma < sumb) || (mina < minb))
    {
        cout << -1 << "\n";
        return;
    }

    i64 ans = suma - sumb + c;
    i64 ans2 = 0;
    for (int i = 0; i < n;i++)
    {
        if(a[i] < b[i])
        {
            goto kkk;
        }

        ans2 += a[i] - b[i];
    }

    cout << min(ans, ans2) << "\n";
    return;
kkk:
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < n;i++)
    {
        if(a[i] < b[i])
        {
            cout << -1 << "\n";
            return;
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
    while(T--)
        solve();

    return 0;
}