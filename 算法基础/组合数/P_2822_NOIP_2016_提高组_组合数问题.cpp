#include <bits/stdc++.h>
using namespace std;
int n, m, k;
const int MAXN = 2e3 + 10;
int c[MAXN][MAXN];
int ans[MAXN][MAXN];
void build()
{
    for (int i = 0; i < MAXN;i++)
    {
        c[i][0] = 1;
        c[i][i] = 1;
    }
    for (int i = 1; i < MAXN; i++)
    {
        for (int j = 1; j <= min(MAXN,i); j++)
        {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % k;
        }
    }
    for (int i = 1; i < MAXN;i++)
    {
        for (int j = 1; j < MAXN;j++)
        {
            if(j <= i)
            ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1] + (c[i][j] == 0);
            else
                ans[i][j] = ans[i][i];
        }
    }
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t >> k;
    build();
    while(t--)
    {
        cin >> n >> m;
        cout << ans[n][m] << "\n";
    }
}