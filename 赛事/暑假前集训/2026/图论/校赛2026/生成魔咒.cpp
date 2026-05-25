#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    string x;
    cin >> x;
    i64 ans = 0;
    for (int i = 0;i < x.size();i++)
    {
        i64 num = x[i] - '0';
        ans = ans * 2 + num;
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--)
        solve();

    return 0;
}