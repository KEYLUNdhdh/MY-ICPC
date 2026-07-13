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
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    map<int, int> mp;
    for (int i = 0; i < n;i++)
        cin >> a[i], mp[a[i]]++;

    if(mp.size() == 1)
    {
        if(mp[a[0]] % 2 == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
        return;
    }
    sort(a.begin(), a.end());
    for (int i = n - 1; i >= 0;)
    {
        int maxx = a[i];
        int cnt = mp[maxx];
        if(cnt % 2 == 0)
        {
            cout << "YES\n";
            return;
        }

        int sch = maxx - k;
        auto it = lower_bound(a.begin(), a.end(), sch) - a.begin();
        if(a[it] != maxx)
        {
            cout << "YES\n";
            return;
        }
        else
        {
            i = it - 1;
        }
    }

    cout << "NO\n";
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