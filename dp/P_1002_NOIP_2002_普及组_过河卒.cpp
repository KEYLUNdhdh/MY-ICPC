#include <iostream>
using namespace std;
#define int long long
int dp[30][30] = {0};
int k[30][30] = {0};
signed main()
{
    int a, b;
    cin >> a >> b;//B
    a += 2;
    b += 2;
    int n, m;
    cin >> n >> m;//ma
    n += 2;
    m += 2;
    k[n][m] = 1;
    k[n - 1][m - 2] = 1;
    k[n - 2][m - 1] = 1;
    k[n - 2][m + 1] = 1;
    k[n - 1][m + 2] = 1;
    k[n + 1][m - 2] = 1;
    k[n + 2][m - 1] = 1;
    k[n + 1][m + 2] = 1;
    k[n + 2][m + 1] = 1;
    dp[2][2] = 1;
    for (int i = 2; i <= a;i++)
        for (int j = 2; j <= b;j++)
        {
            if (i == 2 && j == 2)
                continue;
            if(k[i][j] == 0)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    cout << dp[a][b];
}