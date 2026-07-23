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

#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;

ostream &operator<<(ostream &os, i128 n) {
    string s;
    int f = 0;
    if(n == 0)
        s = "0";
    if(n < 0)
    {
        f = 1;
        n = -n;
    }
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    reverse(s.begin(), s.end());
    if(f)
        s = '-' + s;
    return os << s;
}

istream &operator>>(istream &is,i128& n)
{
    n = 0;
    string s;
    is >> s;
    int sign = 1, start = 0;
    if(s[0] == '-')
    {
        sign = -1;
        start = 1;
    }
    for (int i = start; i < s.size();i++)
    {
        n = n * 10 + s[i] - '0';
    }
    n *= sign;
    return is;
}

// 这个贪心想不到啊
void solve()
{
    i64 n;
    cin >> n;
    // if(n == 1)
    // {
    //     cout << 0 << "\n";
    //     return;
    // }
    // else if(n == 2)
    // {
    //     cout << 1 << "\n";
    //     return;
    // }
    // else if(n == 3)
    // {
    //     cout << 2 << "\n";
    //     return;
    // }
    // else if(n == 4)
    // {
    //     cout << 4 << "\n";
    //     return;
    // }

    i128 s = sqrtl(n);

    while(s * s > n)
        s--;
    while((s + 1) * (s + 1) <= n)
        s++;
        
    i128 res = n - s * s;
    if(res == 0)
    {
        i128 ans = 4 * n - 4 * s;
        ans /= 2;
        cout << ans << "\n";
    }
    else if(res <= s)
    {
        i128 ans = 4 * n - (4 * s + 2);
        ans /= 2;
        cout << ans << "\n";
    }
    else
    {
        i128 ans = 4 * n - (4 * s + 4);
        ans /= 2;
        cout << ans << "\n";
    }
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