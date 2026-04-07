#include <bits/stdc++.h>
using namespace std;
int dp[1000005] = {0};
int main()
{
    int n;
    cin >> n;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 5;
    for (int i = 4; i <= n;i++)
    {
        dp[i] = dp[i - 1] * 2 % 10000 + dp[i - 3] % 10000;
        dp[i] %= 10000;
    }
    cout << dp[n];
}