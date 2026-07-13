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
    i64 res = 1;
    int cnt = 1;
    vector<int> ans = {1};
    for (int i = 2; i <= n;i++)
        if(gcd(i, n) == 1)
            res = (res * i) % n, cnt++, ans.push_back(i);

    debug(res)
    debugarr(ans)
    if(res == 1)
    {
        cout << cnt << "\n";
        for(int k : ans)
            cout << k << " ";
    }
    else
    {
        cout << cnt - 1 << "\n";
        for(int k : ans)
            if(k != res)
                cout << k << " ";
    }

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