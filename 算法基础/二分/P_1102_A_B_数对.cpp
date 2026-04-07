#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N];
signed main()
{
    int n, c;
    cin >> n >> c;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    int cnt = 0;
    for (int i = 0; i < n;i++)
    {
        int tp = a[i] + c;
        auto it = lower_bound(a, a + n, tp);
        if(*it == tp)
        {
            auto itt = upper_bound(a, a + n, tp);
            cnt += itt - it;
        }
    }
    cout << cnt;
}