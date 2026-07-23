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
    vector<int> a(n), b(n);
    int suma = 0, sumb = 0;
    int to0 = 0, to1 = 0;
    int f = 1;
    for (int i = 0; i < n;i++)
        cin >> a[i], suma += a[i];
    for (int i = 0; i < n;i++)
    {
        cin >> b[i], sumb += b[i];
        if(a[i] != b[i])
        {
            f = 0;
            if(a[i] == 1)
                to0++;
            else
                to1++;
        }
    }

    if(f)
    {
        cout << 0 << "\n";
        return;
    }

    if(suma == 0)
    {
        if(sumb == 0)
            cout << 0 << "\n";
        else
            cout << -1 << "\n";
        return;
    }

    if(to0 & 1)
        cout << 1 << "\n";
    else
    {
        if(to0 != 0)
            cout << 2 << "\n";
        else
        {
            if(sumb == n)
                cout << -1 << "\n";
            else
                cout << 2 << "\n";
        }
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