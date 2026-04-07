#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
int a[1000005] = {0};
// int cnt[1000005] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        // int minn = 0x3f3f3f3f;
        int minn = 0x3f3f3f3f;
        for (int i = 1; i <= n;i++)
        {
            cin >> a[i];
            minn = min(minn, a[i]);
        }
        if (m < minn)
        {
            for (int i = 0; i < n;i++)
                cout << "0 ";
            cout << "\n";
            continue;
        }
        int left = m % minn;
        for (int i = 1; i <= n;i++)
        {
            int res;
            if (a[i] == minn)
            {
                res = m / minn;
            }
            else
            {
                int dis = a[i] - minn;
                res = min(left / dis,m / minn);
            }
            cout << res << " ";
        }
        cout << "\n";
    }
}