#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N] = {0};
int ans[N] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n;i++)
        {
            cin >> a[i];
        }
        ans[0] = 0;
        for (int i = 1; i < n;i++)
        {
            ans[0] -= a[i];
        }
        ans[1] = 0;
        ans[1] += a[0];
        for (int i = 2; i < n;i++)
        {
            ans[1] -= a[i];
        }
        int maxx = max(ans[0],ans[1]);
        for (int i = 2; i < n;i++)
        {
            ans[i] = ans[i - 1] + abs(a[i - 1]) + a[i];
            maxx = max(maxx, ans[i]);
        }
        cout << maxx << "\n";
    }
}