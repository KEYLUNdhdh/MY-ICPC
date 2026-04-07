#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int t;
    cin >> t;
    int a[50] = {0};
    while (t--)
    {
        int s, x;
        cin >> s >> x;
        if (s == 1)
        {
            a[x]++;
        }
        else
        {
            int index = 0;
            int b[50] = {0};
            for (int i = 0; i < 50;i++)
            {
                b[i] = a[i];
            }
            int flag = 0;
            while (x > 0)
            {
                if (x & 1)
                {
                    if (b[index] >= 1)
                    {
                        b[index]--;
                        b[index + 1] += b[index] / 2;
                        index++;
                    }
                    else
                    {
                        flag = 1;
                        cout << "NO\n";
                        break;
                    }
                }
                else
                {
                    b[index + 1] += b[index] / 2;
                    index++;
                }
                x >>= 1;
            }
            if (!flag)
            cout << "YES\n";
        }
    }
}