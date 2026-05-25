#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve()
{
    while(1)
    {
        int f = 0;
        for (int i = 0; i <= 100;i++)
        {
            if(i == 100)
            {
                cout << "! " << i << endl;
                cout.flush();
                f = 1;
                return;
            }
            cout << "? " << i << endl;
            cout.flush();
            string g;
            cin >> g;
            if(g == "YES")
            {
                cout << "! " << i << endl;
                cout.flush();
                return;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}