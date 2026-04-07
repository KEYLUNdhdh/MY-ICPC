#include <bits/stdc++.h>
using namespace std;
int dp[25][25] = {0};
int main()
{
    int n;
    cin >> n;
    for (int x = 0; x<= n;x++)
    {
        for (int y = 0; y <= n;y++)
        {
            if (x == 0)
            {
                dp[x][y] = 1;
            }
            else if (y ==0)
            {
                dp[x][y] = dp[x - 1][y + 1];
            }
            else
                dp[x][y] = dp[x - 1][y + 1] + dp[x][y - 1];
        }
    }
    // cout << dp[0][n];
    cout << dp[n][0];
}