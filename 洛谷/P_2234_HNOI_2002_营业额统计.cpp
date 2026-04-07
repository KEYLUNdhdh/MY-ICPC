#include <bits/stdc++.h>
#define int long long
using namespace std;
//lower_bound 返回第一个大于等于x的地址
//upper_bound 返回第一个大于x 的地址
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    set<int> history;
    int ans = 0;
    for (int i = 1; i <= n;i++)
    {
        int neww;
        cin >> neww;
        if(i == 1)
        {
            ans += neww;
        }
        else
        {
            auto it = history.lower_bound(neww);
            int minn = 2e15;
            if(it != history.end())
            {
                minn = min(minn, abs(*it - neww));
            }
            if (it != history.begin())
            {
                it--;
                minn = min(minn, abs(*it - neww));
            }
            ans += minn;
        }
        history.insert(neww);
    }
    cout << ans;
}