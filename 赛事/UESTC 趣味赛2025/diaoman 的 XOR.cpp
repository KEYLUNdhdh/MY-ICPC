#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> a;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        if (n == 1)
        {
            cout << "0\n";
            continue;
        }
        if (n == 2)
        {
            cout << "-1\n";
            continue;
        }
        int pre = 0;
        for (int i = 1; i <= n -2;i++)
        {
            a.push_back(i);
            pre ^= i;
        }
        int big = 1 << 30;
        if (pre == 0)//重复
        {
            a.pop_back();
            a.push_back(0);
            pre = n - 2;
        }
        a.push_back(big);
        a.push_back(big ^ pre);
        for (int i = 0; i < n;i++)
        {
            cout << a[i] << " ";
        }
        cout << "\n";
        a.clear();
    }
}