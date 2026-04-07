#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[500005] = {0};
int l[500005] = {0};
int r[500005] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    l[1] = 1;
    for (int i = 2, j = 1; i <= n;i++)
    {
        while(a[i] - a[j] > k)
            j++;
        l[i] = max(l[i - 1], i - j + 1);
    }
    r[n] = 1;
    for (int i = n - 1, j = n; i >= 1;i--)
    {
        while (a[j] - a[i] > k)
            j--;
        r[i] = max(r[i + 1], j - i + 1);
    }
    int maxx = 0;
    for (int i = 1; i <= n - 1;i++)
        maxx = max(maxx, l[i] + r[i + 1]);
    cout << maxx;
}