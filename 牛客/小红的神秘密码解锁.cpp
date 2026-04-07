#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int a[MAXN];
signed main()
{
    string s;
    cin >> s;
    int c1 = 0, c2 = 0;
    for (int i = 0; i < s.size() - 1;i++)
    {
        if(s[i] != s[i + 1])
            c1++;
        else
            c2++;
    }
    cout << c1 * c2 + 1;
    // auto C = [&](int n, int m)
    // {
    //     m = min(m, n - m);
    //     int ans = 1;
    //     for (int i = 1; i <= m;i++)
    //         ans = ans * (n - i + 1) / (m - i + 1);
    //     return ans;
    // };

}