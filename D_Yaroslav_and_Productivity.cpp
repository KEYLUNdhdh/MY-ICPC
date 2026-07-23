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
    int n, m;
    cin >> n >> m;

    vector<i64> a(n + 1, 0);
    vector<i64> prefix(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i], prefix[i] = prefix[i - 1] + a[i];

    vector<i64> b(m + 1, 0);
    for (int i = 1; i <= m;i++)
        cin >> b[i];

    sort(b.begin(), b.end());
    // debugarr(b)

  
    i64 ans = 0;
    if(b.size() == 2)
    {
        i64 tmp = prefix[b[1]];
        ans = abs(tmp) + prefix[n] - prefix[b[1]];
        cout << ans << "\n";
        return;
    }
    for (int i = 1; i <= m;i++)
    {
        int l = b[i - 1] + 1;
        int r = b[i];

        i64 tmp = prefix[r] - prefix[l - 1];
        ans += abs(tmp);
    }

    int lw = b.back();
    ans += prefix[n] - prefix[lw];
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