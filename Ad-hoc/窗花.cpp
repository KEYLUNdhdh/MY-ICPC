#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
const int MOD = 998244353;


void solve()
{
    int n, m;
    cin >> n >> m;
    if(abs(n - m) > 1)
        cout << -1;
    else
    {
        if(n == m)
        {
            for (int i = 1; i <= n;i++)
            {
                for (int j = 1; j <= m;j++)
                {
                    if(j == i || j == i + 1)
                        cout << 1;
                    else
                        cout << 0;
                }
                cout << "\n";
            }
        }
        else if(n == m + 1)
        {
            for (int i = 1; i <= n;i++)
            {
                for (int j = 1; j <= m;j++)
                {
                    if(j == i || j == i - 1)
                        cout << 1;
                    else
                        cout << 0;
                }
                cout << "\n";
            }
        }
        else if(n + 1 == m)
        {
            for (int i = 1; i <= n;i++)
            {
                for (int j = 1; j <= m;j++)
                {
                    if(j == i || j == i + 1)
                        cout << 1;
                    else
                        cout << 0;
                }
                cout << "\n";
            }
        }
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