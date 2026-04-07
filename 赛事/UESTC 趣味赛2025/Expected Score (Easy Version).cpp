#include <bits/stdc++.h>
#define ld long double
#define int long long
using namespace std;
int a[100005] = {0};
int b[100005] = {0};
int cnta[10005] = {0};
int cntb[10005] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    int maxa = 0, maxb = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        cnta[a[i]]++;
        maxa = max(maxa, a[i]);
    }
    for (int i = 1; i <= m;i++)
    {
        cin >> b[i];
        cntb[b[i]]++;
        maxb = max(maxb, b[i]);
    }
    ld pa,pb;
    ld ans = 0;
    for (int i = 1; i <= maxa;i++)
    {
        if (cnta[i] == 0)
            continue;
        else
        {
            pa = (ld)cnta[i] / (ld)n;
            for (int j = 1; j <= maxb;j++)
            {
                if (cntb[j] == 0)
                    continue;
                pb = (ld)cntb[j] / (ld)m;
                ans += (ld)abs(i - j) * (ld)(i + j) * pa * pb;
            }
        }
    }
    cout << fixed << setprecision(10) << ans;
}