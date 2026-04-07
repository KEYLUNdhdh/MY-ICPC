#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[1000005] = {0};
signed main()
{
    int t;
    cin >> t;
    int n, k;
    while (t--)
    {
        cin >> n >> k;
        int pos = 0x3f3f3f3f;
        for (int i = n; i >= 1;i--)
        {
            if (i % k == 0)
            {
                if (i == n)
                {
                    dp[i] = 0;
                    pos = i;
                    continue;
                }
                else
                {
                    dp[i] = dp[i + 1];
                    pos = i;
                }
            }
            else
            {
                if(i == n)
                {
                    dp[i] = 1;
                    pos = i;
                    continue;
                }
                else
                {
                    dp[i] = dp[i + 1] + pos - i;
                }
            }
        }
        int total = n * (n + 1) / 2;
        // cout << dp[1] << " ";
        cout << total - dp[1] << "\n";
    }
}