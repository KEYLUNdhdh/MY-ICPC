#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 5;
const int INF = 0x3f3f3f3f;
int vis[MAXN];
int dp[MAXN];
int n;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--)
    { 
        cin >> n;
        for (int i = 1; i <= n;i++)
        {
            dp[i] = INF;
            vis[i] = 0;
        }
        int tp;
        for (int i = 1; i <= n;i++)
        {
            cin >> tp;
            if(tp <= n)
                vis[tp] = 1;
        }
        dp[1] = 0;
        for (int i = 1; i <= n;i++)
        {
            if(dp[i] == INF)
                continue;
            for (int k = 2; i * k <= n;k++)
            {
                if(vis[k])
                {
                    if(dp[i] + 1 < dp[i * k])
                        dp[i * k] = dp[i] + 1;
                }
            }
        }
        for (int i = 1; i <= n;i++)
        {
            if(i == 1)
            {
                if(vis[1])
                    cout << 1 << " ";
                else
                    cout << -1 << " ";
            }
            else
            {
                if(dp[i] == INF)
                    cout << -1 << " ";
                else
                    cout << dp[i] << " ";
            }
        }
        cout << "\n";
    }
}