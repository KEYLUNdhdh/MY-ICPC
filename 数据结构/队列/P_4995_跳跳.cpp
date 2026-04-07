#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 305;
signed main()
{
    int n;
    cin >> n;
    deque<int> d(n);
    for (int i = 0; i < n;i++)
        cin >> d[i];
    sort(d.begin(), d.end());
    d.push_front(0);
    int end = 1;
    int ans = 0;
    while(d.size() > 1)
    {
        if(end)
        {
            ans += (d.back() - d.front())*(d.back() - d.front());
            d.pop_front();
            end = 0;
        }
        else
        {
            ans += (d.back() - d.front()) * (d.back() - d.front());
            d.pop_back();
            end = 1;
        }
    }
    cout << ans;
}