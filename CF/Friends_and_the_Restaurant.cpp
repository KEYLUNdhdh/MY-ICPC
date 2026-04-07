#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 5;
int x[MAXN] = {0};
int y[MAXN] = {0};
int dis[MAXN] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n;i++)
            cin >> x[i];
        for (int i = 1; i <= n;i++)
            cin >> y[i];
        for (int i = 1; i <= n;i++)
        {
            dis[i] = y[i] - x[i];
        }
        sort(dis + 1, dis + n + 1);
        int i = 1;
        int j = n;
        int cnt = 0;
        while (i < j)
        {
            if(dis[i] + dis[j] < 0)
            {
                i++;
            }
            else
            {
                cnt++;
                i++;
                j--;
            }
        }
        cout << cnt << "\n";
    }
}