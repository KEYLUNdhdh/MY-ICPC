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

void solve()
{
    int n;
    cin >> n;

    vector<i128> d(n * 2, 0);
    map<i128, int> mp;
    for (int i = 0; i < 2 * n;i++)
        cin >> d[i], mp[d[i]]++;

    for(auto &[x, cnt] : mp)
    {
        if(cnt & 1)
        {
            cout << "NO\n";
            return;
        }
    }

    for (int i = 0; i < 2 * n;i++)
    {
        if(d[i] & 1)
        {
            cout << "NO\n";
            return;
        }
    }

    sort(d.begin(), d.end());
    d.erase(unique(d.begin(), d.end()), d.end());
    if(d.size() < n)
    {
        cout << "NO\n";
        return;
    }

    i128 suf = 0;
    for (int i = n - 1; i >= 0;i--)
    {
        i128 tmp = d[i] - suf * 2;
        i128 up = (i + 1) * 2;
        // debug(up)
        // debug(suf)
        // debug(tmp)
        // cutline
        if(tmp % up != 0)
        {
            cout << "NO\n";
            return;
        }

        if(tmp / up <= 0)
        {
            cout << "NO\n";
            return;
        }
        suf += tmp / up;
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