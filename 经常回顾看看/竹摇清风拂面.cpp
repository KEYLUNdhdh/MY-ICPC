#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 505;
int a[N];
int dp[N][N];
int n;
string s;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        memset(dp, 0x3f3f3f3f3f3f3f3f, sizeof dp);
        cin >> s;
        for (int i = 0; i < n;i++)
            cin >> a[i];
        for (int i = 1; i <= n;i++)
        {
            dp[i][i - 1] = 0;
        }
        for (int l = 2; l <= n;l += 2)
        {
            for (int i = 0; i <= n - l;i++)
            {
                int j = i + l - 1;
                for (int k = i + 1; k <= j;k += 2)
                {
                    if(s[i] == s[k] && dp[i + 1][k - 1] != 0x3f3f3f3f3f3f3f3f && dp[k + 1][j] != 0x3f3f3f3f3f3f3f3f)
                    {
                        dp[i][j] = min(dp[i][j], a[i] * a[k] + dp[i + 1][k - 1] + dp[k + 1][j]);
                    }
                }
            }
        }
        if(dp[0][n - 1] != 0x3f3f3f3f3f3f3f3f)
            cout << dp[0][n - 1] << "\n";
        else
            cout << -1 << "\n";
    }
}