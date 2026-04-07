#include <bits/stdc++.h>
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
//dp直接去模拟试错，O(n * n)
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n;i++)
        cin >> a[i];
    for (int i = 0; i < n;i++)
        cin >> b[i];
    vector<int> dp(2500, 0);
    dp[0] = 1;
    for (int i = 0; i < n;i++)
    {
        vector<int> nxt(2500, 0);
        for (int k = 0; k < 2500;k++)
        {
            if(dp[k] == 1)
            {
                int m = max(0, k - a[i]);
                int mm = k ^ b[i];
                nxt[m] = 1, nxt[mm] = 1;
            }
        }
        dp = nxt;
    }
    for (int i = 2400; i >= 0;i--)
    {
        if(dp[i])
        {
            cout << i;
            break;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}