#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
const int INF = 1e6 + 5;
int n, a[MAXN],cnt[MAXN];
int ans[MAXN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    int maxa = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        maxa = max(maxa, a[i]);
    }
    for (int i = 0; i < n;i++)
    {
        int k = a[i];
        for (int j = 1; j * j <= k; j++)
        {
            if(k % j == 0)
            {
                if(j * j == k)
                {
                    cnt[j]++;
                }
                else
                {
                    cnt[j]++;
                    cnt[k / j]++;
                }
            }
        }
    }
    for (int i = 1; i <= maxa;i++)
    {
        ans[cnt[i]] = max(ans[cnt[i]], i);
    }
    for (int i = n - 1; i >= 1;i--)
    {
        ans[i] = max(ans[i], ans[i + 1]);
    }
    for (int i = 1; i <= n;i++)
        cout << ans[i] << "\n";
}