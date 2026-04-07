#include <bits/stdc++.h>
using namespace std;
int a[200005] = {0};
int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int r, n;
        cin >> r >> n;
        for (int i = 0; i < n;i++)
            cin >> a[i];
        if (n == 1)
        {
            cout << "0\n";
            continue;
        }
        else
        {
            cout << n << "\n";
        }
    }
}