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
    string s;
    cin >> s;

    int d = 0, u = 0;
    for (char c : s)
        if(c == '+')
            u++;
        else
            d++;
    // debug(d)debug(u)
    int q;
    cin >> q;
    while(q--)
    {
        i64 a, b;
        cin >> a >> b;
        // debug(a)debug(b)
        i64 dis = abs(u - d);
        if(dis == 0)
        {
            cout << "YES\n";
            continue;
        }
        i64 lcm = (a * b) / gcd(a, b);
        i64 atol = lcm / a, btol = lcm / b;
        i64 del = abs(atol - btol);
        // debug(atol)debug(btol)
        // debug(del) debug(dis)
        // if(del > dis)
        // {
        //     cout << "NO\n";
        //     continue;
        // }
        if(del == 0)
        {
            if(u == d)
                cout << "YES\n";
            else
                cout << "NO\n";
            continue;
        }
        if(dis % del != 0)
        {
            cout << "NO\n";
            continue;
        }
        i64 minncnt = dis / del;
        if(u > d)
            swap(u, d);
        if(atol > btol)
            swap(atol, btol);
        // debug(minncnt)debug(a)debug(b)debug(atol)debug(btol)
        // cutline
        if(atol * minncnt <= u && btol * minncnt <= d)
            cout << "YES\n";
        else
            cout << "NO\n";
        // i64 total = minncnt * (atol + btol);
        // if(total)
    }
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
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}