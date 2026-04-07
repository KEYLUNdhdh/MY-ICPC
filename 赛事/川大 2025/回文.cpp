#include <bits/stdc++.h>
using namespace std;
int dp[5005][5005] = {0};
int main()
{
    string s;
    cin >> s;
    // s = " " + s;
    for (int i = s.size() - 1; i >= 0;i--)
    {
        for (int j = i; j <= s.size() - 1;j++)
        {
            if (i == j)
            {
                dp[i][j] = 0;
                continue;
            }
            if (s[i] == s[j])
            {
                dp[i][j] = (j - i == 1) ? 0 : dp[i + 1][j - 1];
            }
            else
            {
                    dp[i][j] = min(min(dp[i + 1][j], dp[i][j - 1]), dp[i + 1][j - 1]) + 1;
            }

        }
    }
    cout << dp[0][s.size() - 1];
}