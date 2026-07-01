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
    i64 n, k, d1, d2;
    cin >> n >> k >> d1 >> d2;

    if(n % 3 != 0)
    {
        cout << "no\n";
        return;
    }

    i64 up = n / 3;
    i64 num1 = d2 + k - d1;
    if(num1 % 3 == 0 && num1 >= 0)
    {
        i64 b1 = num1 / 3;
        i64 a = b1 + d1;
        i64 c = k - d1 - 2 * b1;
        if(c >= 0 && a <= up && b1 <= up && c <= up)
        {
            cout << "yes\n";
            return;
        }
    }

    i64 num2 = k - d2 - d1;
    if(num2 % 3 == 0 && num2 >= 0)
    {
        i64 b2 = num2 / 3;
        i64 a = b2 + d1;
        i64 c = k - d1 - 2 * b2;
        if(c >= 0 && a <= up && b2 <= up && c <= up)
        {
            cout << "yes\n";
            return;
        }
    }

    num1 = k + d1 + d2;
    if(num1 % 3 == 0 && num1 >= 0)
    {
        i64 b1 = num1 / 3;
        i64 a = b1 - d1;
        i64 c = k + d1 - 2 * b1;
        if(c >= 0 && a >= 0 && a <= up && b1 <= up && c <= up)
        {
            cout << "yes\n";
            return;
        }
    }

    num2 = k + d1 - d2;
    if(num2 % 3 == 0 && num2 >= 0)
    {
        i64 b2 = num2 / 3;
        i64 a = b2 - d1;
        i64 c = k + d1 - 2 * b2;
        if(c >= 0 && a >= 0 && a <= up && b2 <= up && c <= up)
        {
            cout << "yes\n";
            return;
        }
    }

    cout << "no\n";
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