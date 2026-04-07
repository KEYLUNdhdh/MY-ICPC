#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int a[MAXN];
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n;i++)
            cin >> a[i];
        int index = 1;
        int op = 0x3f3f3f3f;
        for (int i = 1; i <= n;i++)
        {
            if(a[i] != n - i + 1)
            {
                index = i;
                op = n - i + 1;
                break;
            }
        }
        int po = 1;
        for (int i = 1; i <= n;i++)
        {
            if(a[i] == op)
            {
                po = i;
                break;
            }
        }
        int l = index <= po ? index : po;
        int r = index > po ? index : po;
        for (int i = 1; i < l;i++)
            cout << a[i] << " ";
        for (int i = r; i >= l;i--)
            cout << a[i] << " ";
        for (int i = r + 1; i <= n;i++)
            cout << a[i] << " ";
        cout << "\n";
    }
}