#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005] = {0};
int b[1000005] = {0};
int c[1000005] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, x;
        cin >> n >> x;
        // if (x == 0)
        // {
        //     cout << "Yes\n";
        //     continue;
        // }
        //0 is top //n - 1 is bottom
        for (int i = 0; i < n;i++)
            cin >> a[i];
        for (int i = 0; i < n;i++)
            cin >> b[i];
        for (int i = 0; i < n;i++)
            cin >> c[i];
        int aa = 0;
        for (int i = 0; i < n;i++)
        {
            if ((a[i] | x) == x)
            {
                aa |= a[i];
            }
            else
                break;
        }
        int bb = 0;
        for (int i = 0; i < n;i++)
        {
            if ((b[i] | x) == x)
            {
                bb |= b[i];
            }
            else
                break;
        }
        int cc = 0;
        for (int i = 0; i < n;i++)
        {
            if ((c[i] | x) == x)
            {
                cc |= c[i];
            }
            else
                break;
        }
        if ((aa | bb | cc) == x)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}