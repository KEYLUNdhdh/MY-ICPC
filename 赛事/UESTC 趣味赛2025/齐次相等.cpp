#include <iostream>
#define int long long
using namespace std;
int a[1000005] = {0};
int b[1000005] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n;i++)
            cin >> a[i];
        for (int i = 0; i < n;i++)
            cin >> b[i];
        int flag1 = 0;
        int index = 0;
        int foundp = 0;
        for (int i = 0; i < n; i++)
        {
            // if (a[index] == b[index] && a[index] == 0)
            // {
            //     continue;
            // }
            // if (a[index] != b[index] &&(b[index] == 0 || a[index] == 0))
            // {
            //     cout << "NO\n";
            //     flag = 1;
            //     break;
            // }

            if (a[i] == 0 && b[i] == 0)
                continue;
            if (a[i] == 0 && b[i] != 0)
            {
                flag1 = 1;
                break;
            }
            if (a[i] != 0 && b[i] == 0)
            {
                flag1 = 1;
                break;
            }
            if (!foundp)
            {
                index = i;
                foundp = 1;
            }
        }
        if (flag1)
        {
            cout << "NO\n";
            continue;
        }
        int flag2 = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] == 0 && b[i] == 0)
                continue;
            if (b[i] * a[index] != a[i] * b[index])
            {
                flag2 = 1;
                break;
            }
            }
        if (flag2)
        {
            cout << "NO\n";
        }
        else
            cout << "YES\n";
    }

}
