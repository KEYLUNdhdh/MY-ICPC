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

vector<i64> inv;
void invarr(int n,i64 p)
{
    inv.assign(n + 5, 0);
    inv[1] = 1;
    for (int i = 2; i <= n;i++)
        inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    return;
}

void solve()
{
    int n;
    cin >> n;

    invarr(n + 5, MOD);

    vector<i64> a(n + 1, 0);
    vector<i64> p(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i], p[i] = (p[i - 1] + a[i]) % MOD;

    i64 ans = 0;
    // debug(ans)
    if(n % 2 == 0)
    {
        int step = n / 2;
        i64 cur = p[n];
        // debug(cur)
        int l = 1, r = n;
        for (int i = 1; i <= step;i++)
        {
            ans = (ans + cur * inv[i]) % MOD;
            ans = (ans + cur * inv[n - i + 1]) % MOD;
            l++, r--;
            cur = ((cur + p[r] - p[l - 1]) % MOD + MOD) % MOD;
        }
    }
    else
    {
        int step = (n + 1) / 2;
        i64 cur = p[n];
        // debug(cur)
        int l = 1, r = n;
        for (int i = 1; i < step;i++)
        {
            ans = (ans + cur * inv[i]) % MOD;
            ans = (ans + cur * inv[n - i + 1]) % MOD;
            l++, r--;
            cur = ((cur + p[r] - p[l - 1]) % MOD + MOD) % MOD;
        }
        // cur += a[step];
        ans = (ans + cur * inv[step]) % MOD;
    }
    cout << ans;
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