#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
int w[100005] = {0};
int c[100005] = {0};
//designed by lyc_fan_club of xl
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int sum = 0;
        int n,x,d;cin >> n >> x >> d;
    for (int i = 1; i <= n;i++)
        cin >> w[i];
    for (int i = 1; i <= n;i++)
        {
            cin >> c[i];
        }
        for (int i = 2; i <= x;i++)
        {
            sum += c[i];
        }
        // //看看最大生产值是否在x前出现
        // int maxl = 1;//索引
        // for (int i = 2; i <= n;i++)
        // {
        //     if(w[i] > w[maxl])
        //         maxl = i;
        // }
        // //先升级到maxl，产出一会，最后升级到x
        // if (maxl < x)
        // {
        //     int yield = (d - sum) * w[maxl];
        //     cout << yield << "\n";
        //     continue;
        // }
        // else{
        // int yield = (d - sum) * w[x];
        // //往后检查
        // for (int i = x + 1; i <= n;i++)
        // {
        //     sum += c[i];
        //     if (sum > d)
        //         break;
        //     int temp = (d - sum) * w[i];
        //     yield = max(yield, temp);
        // }
        // cout << yield << "\n";
        int cost[100005] = {0};
        for (int i = 2; i <= n;i++)
        {
            cost[i] = cost[i - 1] + c[i];
        }
        if (cost[x] > d)
        {
            cout << -1 << "\n";
            continue;
        }
        int maxw[100005] = {0};
        maxw[1] = w[1];
        for (int i = 2; i <= n;i++)
        {
            maxw[i] = max(maxw[i - 1], w[i]);
        }
        int yield = 0;
        for (int i = x; i <= n;i++)
        {
            int cos = cost[i];
            if (cos > d)
                break;
            int temp = (d - cos) * maxw[i];
            yield = max(yield, temp);
        }
        cout << yield << "\n";
    }
    }
    