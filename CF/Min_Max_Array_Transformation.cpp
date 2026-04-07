#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N] = {0};
int b[N] = {0};
int d[N] = {0};
int n;
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        for (int i = 0; i < n;i++)
            cin >> a[i];
        for (int i = 0; i < n;i++)
            cin >> b[i];
        int ind = 0;
        int jb = 0;
        int ia = 0;
        while(ia < n)
        {
            if (b[jb]  - a[ia] >= 0)
            {
                d[ia] = b[jb] - a[ia];
                ia++;
            }
            else
            {
                jb++;
            }
        }
        for (int i = 0; i < n;i++)
            cout << d[i] << " ";
        cout << "\n";
        int max = n - 1;
        int reai = n - 1;
        while (reai > -1)
        {
            d[reai] = b[max] - a[reai];
            if (reai >= 1 && a[reai] > b[reai - 1])
            {
                max = reai - 1;
            }
            reai--;
        }
        for (int i = 0; i < n;i++)
            cout << d[i] << " ";
        cout << "\n";
    }
}