#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3005;
int a[N];
signed main()
{
    int t;
    cin >> t;
    int n;
    while(t--)
    {
        cin >> n;
        for (int i = 0; i < n;i++)
        {
            cin >> a[i];
            
        }
        sort(a, a + n);
        int cnt = 0;
        int tp = 1;
        if(n == 1)
        {
            cout << 1 << "\n";
            continue;
        }
        else
        {
            for (int i = 0; i < n - 1;i++)
            {
                if(a[i] + 1 == a[i + 1])
                {
                    tp++;
                }
                else if(a[i] == a[i + 1])
                {
                    continue;
                }
                else
                {
                    cnt = max(cnt, tp);
                    tp = 1;
                }
            }
        }
        cnt = max(cnt, tp);
        cout << cnt << "\n";
    }
}
