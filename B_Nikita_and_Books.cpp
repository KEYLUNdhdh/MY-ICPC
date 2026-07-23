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
    int n;
    cin >> n;

    vector<i64> a(n);
    i64 sum = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        sum += a[i];
    }

    i64 lb = (n + 1) * n / 2;
    if(sum < lb)
    {
        cout << "NO\n";
        return;
    }
    
    if(n == 1)
    {
        cout << "YES\n";
        return;
    }
    for (int i = 0; i < n;i++)
    {
        i64 cur = i + 1;
        if(a[i] < cur)
        {
            cout << "NO\n";
            return;
        }
        i64 up = a[i] - cur;
        a[i] -= cur;
        if(i + 1 < n)
            a[i + 1] += up;
    }

    cout << "YES\n";
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