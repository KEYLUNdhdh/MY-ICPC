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

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    if(n == 1)
    {
        if(a[1] == 1)
            cout << "Alice\n";
        else
            cout << "Bob\n";
        return;
    }
    else if(n == 2)
    {
        if((a[1] == 1 && a[2] == 1) || (a[1] == 0 && a[2] == 0))
            cout << "Bob\n";
        else
            cout << "Alice\n";
        return;
    }

    int maxx = 0;
    int cnt = 0;
    int f1 = 0;
    for (int i = 1; i <= n;i++)
    {
        if(a[i] == 1)
            cnt++;
        else
        {
            if(cnt == 1)
                f1 = 1;
            chmax(maxx, cnt);
            cnt = 0;
        }
    }

    chmax(maxx, cnt);
    if(cnt == 1)
        f1 = 1;

        
    if(maxx == 1)
    {
        cout << "Alice\n";
        return;
    }
    else if(maxx == 2)
    {
        if(f1)
            cout << "Alice\n";
        else
            cout << "Bob\n";
    }
    else if(maxx == 0)
        cout << "Bob\n";
    else
        cout << "Alice\n";
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