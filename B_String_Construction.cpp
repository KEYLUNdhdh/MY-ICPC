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
    int n, k;
    cin >> n >> k;

    int ub = n - 2;
    if(k > ub)
    {
        cout << "-1\n";
        return;
    }

    string s = "";
    for (int i = 3; i <= n;i++)
        if(i & 1)
            s.push_back('0');
        else
            s.push_back('1');

    string s0 = "0", s1 = "1";
    for (int i = 1; i <= k;i++)
    {
        char c = s.back();
        s.pop_back();
        if(c == '0')
            s0.push_back(c);
        else
            s1.push_back(c);
    }
    debug(s0)debug(s1)
    cout << s0 << s1 << s << "\n";

    // if(n % 2 == 0)
    // {
    //     int ub = n - 2;
    //     if(k % 2 || k > ub)
    //     {
    //         cout << "-1\n";
    //         return;
    //     }

    //     int len = k / 2 + 1;
    //     for (int i = 1; i <= len;i++)
    //         cout << 0;
    //     for (int i = 1; i <= len;i++)
    //         cout << 1;
    //     int res = n - 2 * len;
    //     for (int i = 1; i <= res;i++)
    //         if(i & 1)
    //             cout << 0;
    //         else
    //             cout << 1;
    //     cout << "\n";
    // }
    // else// 0 > 1
    // {
    //     int ub = n - 2;
    //     if(k > ub)
    //     {
    //         cout << "NO\n";
    //         return;
    //     }

    //     string s = "";
    //     for (int i = 3; i <= n;i++)
    //         if(i & 1)
    //             s.push_back('0');
    //         else
    //             s.push_back('1');

    //     string s0 = "0", s1 = "1";
    //     for (int i = 1; i <= k;i++)
    //     {
    //         char c = s.back();
    //         s.pop_back();
    //         if(c == '0')
    //             s0.push_back(c);
    //         else
    //             s1.push_back(c);
    //     }
    //     debug(s0)debug(s1)
    //     cout << s0 << s1 << s << "\n";
    // }
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
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}