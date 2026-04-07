#include <bits/stdc++.h>
using namespace std;
int a[10000] = {0};
int n;
int dp[10000] = {0};
int main()
{
    cin >> n;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n;i++)
    {
        dp[i] = 1;
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (a[i] > a[j])
            {
                dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
    }
    int max1 = 0;
    for (int i = 1; i <= n; i++)
    {
        max1 = max(max1, dp[i]);
    }
    cout << max1;
}