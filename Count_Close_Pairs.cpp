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

    auto query = [&](int i, int j) -> int
    {
        cout << "? " << i << " " << j << "\n";
        cout.flush();
        string s;
        cin >> s;

        if(s == "Yes")
            return 1;
        else
            return 0;
    };

    int l = n - 1;
    i64 ans = 0;
    for (int r = n; r >= 2;r--)
    {
        if(l == r)
            l -= 1;
        if(l == 0)
        {
            ans += r - l - 1;
            continue;
        }
        while(l != 0 && query(l, r))
            l--;

        ans += r - l - 1;
    }

    cout << "! " << ans << endl;
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