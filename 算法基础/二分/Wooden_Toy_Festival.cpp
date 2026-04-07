#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[200005] = {0};

bool check(int p,int n)
{
    int i = 0, j = n - 1;
    while (i < n && a[i + 1] - a[0] <=2 * p)
    {
        i++;
    }
    while (j >= 0 && a[n - 1] - a[j - 1] <= 2 * p)
    {
        j--;
    }
    i++, j--;
    if (i >= j || a[j] - a[i] <= 2 * p)
    {
        return true;
    }
    else
    {
        return false;
    }
} 

signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int max_n = 0;
        for (int i = 0; i < n;i++)
        {
            cin >> a[i];
            max_n = max(max_n, a[i]);
        }
        sort(a, a + n);
        int l = -1;
        int r = max_n + 1;
        while (l + 1 != r)
        {
            int mid = l + r >> 1;
            if (check(mid,n))
            {
                r = mid;
            }
            else
            {
                l = mid;
            }
        }
        cout << r << "\n";
    }  
}