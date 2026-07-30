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
    int n;
    cin >> n;

    int k = n / 2;

    vector<int> ord;
    ord.reserve(n);

    ord.push_back(1);

    for (int i = k + 1; i <= n; i++)
        ord.push_back(i);

    for (int i = k; i >= 2; i--)
        ord.push_back(i);

    vector<int> p(n + 1, 0);

    for (int i = 0; i < n; i++)
        p[ord[i]] = ord[(i + 1) % n];

    i64 res = 0;

    for (int i = k + 1; i <= n - 1; i++)
        res += 1ll * (i - 1) * (i - 1);

    for (int i = k; i >= 2; i--)
        res += 1ll * (n - i) * (n - i);

    res += 1ll * (n - 1) * (n - 1);

    cout << res << "\n";

    for (int i = 1; i <= n; i++)
        cout << p[i] << " ";
    cout << "\n";

    cout << n - 1 << "\n";

    for (int i = k + 1; i <= n - 1; i++)
        cout << i << " " << 1 << "\n";

    for (int i = k; i >= 2; i--)
        cout << i << " " << n << "\n";

    cout << n << " " << 1 << "\n";
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}