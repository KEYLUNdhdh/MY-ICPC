#include <iostream>
#include <map> 
#include <algorithm>
#include <vector>
#define int long long
using namespace std;
int a[200005] = {0};
int b[200005] = {0};
int miku[200005] = {0};
multimap<int, int> dis;

void solve()
{
    int suma  =0;
    int n,q;
        cin >> n >> q;
        for (int i = 0;i <n;i++)
            {
                cin >> a[i];
                suma += a[i];
            }
        for (int i = 0; i < n;i++)
            cin >> b[i];
        vector<int> cost(n, 0);
        for (int i = 0; i < n;i++)
            cost[i] = a[i] + b[i];
        sort(cost.begin(),cost.end());
        int qian[210005] = {0};
        for (int i = 0; i < n;i++)
        {
            qian[i + 1] = qian[i]+ cost[i];
        }
        for (int i = 0; i < q;i++)
        {
            int x;
            cin >> x;
            cout << suma - qian[x] << "\n";
        }
}
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t --)
    {
        // int n,q;
        // cin >> n >> q;
        // for (int i = 0;i <n;i++)
        //     cin >> a[i];
        // for (int i = 0; i < n;i++)
        //     cin >> b[i];

        // for (int i = 0; i < n;i++)
        // {
        //     dis.insert(make_pair(a[i] + b[i], i));
        // }
        //     for (int i = 0; i < q; i++) // 询问
        //     {
        //         int x;
        //         cin >> x;
        //         auto it = dis.begin();
        //         for (int i = 0; i < x;i++)
        //         {
        //             miku[i] = it->second;
        //             it++;
        //         }
        //         sort(miku, miku + x);
        //         int sum = 0;
        //         int index = 0;
        //         for (int i = 0; i < n;i++)
        //         {
        //             if (i != miku[index] || index >= x)
        //             {
        //                 sum += a[i];
        //             }
        //             else if (i == miku[index] && index < x)
        //             {
        //                 sum -= b[i];
        //                 index++;
        //             }
        //         }
        //         cout << sum << "\n";
        //     }
        //     dis.clear();
        solve();
}
return 0;
}