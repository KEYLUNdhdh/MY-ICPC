#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
const int INF = 2e11;
int a[MAXN],b[MAXN];
int maxx = -1;int n;
int minn = INF;
struct node{
    int val, id;
};
int check(int k)
{
    vector<node> vec;
    for (int i = 0; i < n;i++)
    {
        //minn 和 maxx一定要联通
        //如果和minn或者maxx联通，那么这个数一定属于一个大的连通分量，它可以借由maxx或者minn到达其他位置，不用考察
        if(abs(a[i] - minn) >= k || abs(a[i] - maxx) >= k)
            continue;
        vec.push_back({a[i],i});
    }
    for (auto it : vec)
    {
        auto low = lower_bound(b, b + n, it.val) - b;
        auto up = upper_bound(b, b + n, it.val) - b;
        if(it.id >= low && it.id <up)
            continue;
        else
        {
            return 0;
        }
    }
    return 1;
}
signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        
        cin >> n;
        int l = -1;
        int r = INF;
        maxx = -1;
        minn = INF;
        for (int i = 0; i < n;i++)
        {
            cin >> a[i];
            b[i] = a[i];
            maxx = max(a[i], maxx);
            minn = min(a[i], minn);
        }
        sort(b, b + n);
        while (l + 1 != r)
        {
            int mid = l + r >> 1;
            if (check(mid))
            {
                l = mid;
            }
            else
                r = mid;
        }
        if(l + 1 == INF)
            cout << -1 << "\n";
        else
            cout << l << "\n";
    }
}