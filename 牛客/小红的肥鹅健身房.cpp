#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k;
map<int, int> mp;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n;i++)
        for (int j = 0; j < m;j++)
        {
            int tp;
            cin >> tp;
            if(tp != 0)
            {
                mp[tp]++;
            }
        }
    int co = 0, cnt = 0;
    while(!mp.empty())
    {
        auto it = mp.begin();
        int key = it->first;
        int val = it->second;
        if(val <= 1)
        {
            mp.erase(it);
            continue;
        }
        else
        {
            int up = val / 2;
            cnt += up;
            if(key + 1 >= k)
                co += up;
            mp[key + 1] += up;
            mp.erase(it);
        }
    }
    cout << cnt  << " " << co;
}
