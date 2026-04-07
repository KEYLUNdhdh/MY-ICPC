#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N] = {0};
int dis[N] = {0};
signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, m;
        cin >> n >> m;
        if(m - 1> n)
        {
            cout << "NO\n";
            continue;
        }
        for (int i = 0; i < n;i++)
        {
            cin >> a[i];
        }
        sort(a, a + n);
        int l = 0;
        int r = m - 2;
        int f = 0;
        while(r != n)
        {
            if(a[r] - a[l] <= m - 1)
            {
                cout << "YES\n";
                f = 1;
                break;
            }
            else
            {
                r++, l++;
            }
        }
        if(f)
        {
            continue;
        }
        else
        {
            cout << "NO\n";
        }
    }
}