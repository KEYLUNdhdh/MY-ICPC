#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
int xa, ya, xb, yb;
map<int, int> mp;
typedef struct point
{
    int x, y, man;
}ppp;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    int a, b;
    while(t--)
    {
        cin >> n;
        cin >> xa >> ya >> xb >> yb;
        vector<ppp> vec(n);
        int p = abs(xa - xb) + abs(ya - yb);
        int tp;
        ppp temp;
        for (int i = 0; i < n;i++)
        {
            cin >> a >> b;
            tp = abs(a - xa) + abs(b - ya) + abs(a - xb) + abs(b - yb);
            temp.x = a;
            temp.y = b;
            temp.man = tp;
            vec[i] = temp;
            mp[tp]++;
        }
        mp[p] += 2;
        // for(auto it : mp)
        // {
        //     int ori = (it.first - p) * 2 + (1 + abs(xa - xb)) * (1 + abs(ya - yb));
        //     cout << ori - it.second << " ";
        // }
        for(auto i : vec)
        {
            // int ori = (i.man - p) * 2 + (1 + abs(xa - xb)) * (1 + abs(ya - yb));
            int ori;
            if(i.man != p)
            ori = i.man * 2;
            else
                ori = (1 + abs(xa - xb)) * (1 + abs(ya - yb));
            cout << ori - mp[i.man] << " ";
        }
            cout << "\n";
        mp.clear();
    }
}