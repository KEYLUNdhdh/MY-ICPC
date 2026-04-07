#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N] = {0};
int n;
signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        for (int i = 0; i < n;i++)
            cin >> a[i];
        sort(a, a + n);
        int cnt = 0;
        int i = 0;
        int j = n - 1;
        int x = 0;
        while(i < j)
        {
            if (x + a[i] >= a[j])
            {
                int need = a[j] - x;
                a[i] -= need;
                cnt += need;
                cnt++;
                x = 0;
                j--;
                if(a[i] == 0)
                    i++;
            }
            else
            {
                x += a[i];
                cnt += a[i];
                i++;
            }
            
        }
        if(i == j)
        {
                if(a[i] > 0)
                {
                if(a[i] <= 1)
                {
                    cnt++;
                }
                else
                    {
                    int now = a[i];
                    if(x >= now)
                    {
                        cnt++;
                    }
                    else
                    {
                        int tp = (now - x + 1) / 2;
                        cnt += tp + 1;
                    }
                    }
                }
        }
        cout << cnt << "\n";
    }
}