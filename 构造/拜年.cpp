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
    int n;
    cin >> n;
    if(n <= 3)
        cout << -1;
    else
    {
        int r = n % 4;
        int k = n / 4;
        vector<int> gou = {2, 4, 1, 3};
        vector<int> r1 = {2, 4, 1, 3, 5};
        vector<int> r2 = {2, 4, 6, 1, 3, 5};
        vector<int> r3 = {2, 7, 4, 6, 1, 3, 5};
        for (int i = 1; i < k;i++)
        {
            int up = (i - 1) * 4;
            cout << 2 + up << " " << 4 + up << " " << 1 + up << " " << 3 + up << " ";
        }
        int up = (k - 1) * 4;
        if(r == 1)
            cout << 2 + up << " " << 4 + up << " " << 1 + up << " " << 3 + up << " " << 5 + up << " ";
        else if(r == 2)
            cout << 2 + up << " " << 4 + up << " " << 6 + up << " " <<  1 + up << " " << 3 + up << " " << 5 + up;
        else if(r == 3)
            cout << 2 + up << " " << 7 + up << " " << 4 + up << " " << 6 + up << " " <<  1 + up << " " << 3 + up << " " << 5 + up;
        else
            cout << 2 + up << " " << 4 + up << " " << 1 + up << " " << 3 + up;
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