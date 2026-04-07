#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;

void solve()
{
    int a, b;
    cin >> a >> b;
    if(a > b)
    {
        int gp = b + 1;
        int num = a / gp;
        int res = a % gp;
        for (int i = 0; i < gp;i++)
        {
            int t = num + (i < res ? 1 : 0);
            for (int j = 0; j < t;j++)
                cout << "0";
            if(i < b)
                cout << "1";
        }
    }
    else
    {
        int gp = a + 1;
        int num = b / gp;
        int res = b % gp;
        for (int i = 0; i < gp; i++)
        {
            int t = num + (i < res ? 1 : 0);
            for (int j = 0; j < t; j++)
                cout << "1";
            if (i < a)
                cout << "0";
        }
    }
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}