#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[100005] = {0};
signed main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n;i++)
        cin >> a[i];
    int ans = 1;
    // sort(a, a + n);
    while (1)
    {
        int flag = 0;
        for (int i = 0; i < n;i++)
        {
            if (a[i]== ans)
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            ans <<= 1;
        }
        else
        {
            cout << ans;
            break;
        }
    }
}