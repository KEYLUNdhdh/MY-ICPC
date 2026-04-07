#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[2500];
signed main()
{
    int n;
    cin >> n;
    memset(a, -1, sizeof(a));
    int test = n + 1;
    int tp;
    while(test--)
    {
        for (int i = 1; i <= 2 * n + 1;i++)
        {
            if (a[i] == -1)
            {
                cout << i << endl;
                a[i] = 0;
                cout.flush();
                break;
            }
        }
        cin >> tp;
        a[tp] = 0;
    }
    return 0;
}