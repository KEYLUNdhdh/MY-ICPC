// 很经典的线性dp 模型，注意到[1,n - 1] 这个子数组的答案不受 an的影响，因此我们可以从前往后dp.
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 998244353;
const int MAXN = 2e5 + 5;
int a[MAXN];
int dp[MAXN];
int prefix[MAXN];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n;i++)
            cin >> a[i];
        dp[0] = 1;
        prefix[0] = 1;
        int r = 1,l = 1;
        int pre = 0;
        while(r <= n)
        {
            if((pre & a[r]) == 0)
            {
                pre |= a[r];
                int ll = l >= 2 ? prefix[l - 2] : 0;
                dp[r] = (prefix[r - 1] -  ll + MOD) % MOD;
                dp[r] %= MOD;
                prefix[r] = dp[r] + prefix[r - 1];
                prefix[r] %= MOD;
                r++;
            }
            else
            {
                while(l < r && ((pre & a[r]) != 0))
                {
                    pre -= a[l];
                    l++;
                }
                pre |= a[r];
                int ll = l >= 2 ? prefix[l - 2] : 0;
                dp[r] = (prefix[r - 1] - ll + MOD) % MOD;
                dp[r] %= MOD;
                prefix[r] = prefix[r - 1] + dp[r];
                prefix[r] %= MOD;
                r++;
            }
        }
        cout << dp[n] << "\n";
    }
}