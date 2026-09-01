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

void solve()
{
    i128 n, k;
    cin >> n >> k;

    i128 lb = (1 + k) * k / 2;
    if(n < lb)
    {
        cout << -1;
        return;
    }
    else if(n == lb)
    {
        for (i128 i = 1; i <= k;i++)
            cout << i << " ";
        return;
    }

    i128 g = 1;
    for (i128 i = 1; i * i <= n;i++)
    {
        if(n % i == 0 && n / i >= lb)
        {
            if(i >= lb)
                chmax(g, n / i);
            if(n / i >= lb)
                chmax(g, i);
        }
        else if(n / i < lb)
            break;
    }
    // debug(g);
    i128 dest = n / g;
    i128 cur = 0;
    // debug(k)
    for (i128 i = 1;i <= k - 1;i++)
    {
        cout << i * g << " ";
        cur += i;
    }
    // debugarr(ans) debug(dest) debug(cur)
    cout << (dest - cur) * g << " ";

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