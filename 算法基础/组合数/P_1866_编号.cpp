#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;

map<int, int> mp;

inline int A(int n,int m)
{
    if(n < m)
        return -1;
    int ans = 1;
    for (int i = 1; i <= m;i++)
    {
        ans = ans * (n - i + 1);
        ans = ans % MOD;
    }
    return ans;
}
signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int m;
        cin >> m;
        mp[m]++;
    }
    int ans = 1;
    int zhan = 0;
    for(auto it : mp)
    {
        int m = it.first;
        int cnt = it.second;
        int res = A(m - zhan, cnt);
        if(res == -1)
        {
            cout << "0";
            return 0;
        }
        ans = ans * res % MOD;
        zhan += cnt;
    }
    cout << ans;
}