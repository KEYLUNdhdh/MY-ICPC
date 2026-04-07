#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
void solve()
{
    int n, c;
    cin >> n >> c;

    vector<i64> a(n), b(n);
    for (int i = 0; i < n;i++)
        cin >> a[i] >> b[i];
    auto check = [&](i64 x) -> bool
    {
        i128 ans = 0;
        for (int i = 0;i < n;i++)
        {
            ans += (i128)a[i] * (i128)x / b[i];
            if(ans >= c - n)
                return true;
        }
        return ans >= c - n;
    };
    i64 l = 0, r = 2e18;
    while(l + 1 < r)
    {
        i64 mid = l + r >> 1;
        if(check(mid))
            r = mid;
        else
            l = mid;
    }

    auto check2 = [&](i64 x) -> bool
    {
        i128 ans = 0;
        for (int i = 0;i < n;i++)
        {
            ans += (i128)a[i] * (i128)x / b[i];
            if (ans > c - n)
                return true;
        }
        return ans > c - n;
    };
    
    i64 ll = 0, rr = 2e18;
    while(ll + 1 < rr)
    {
        i64 mid = ll + rr >> 1;
        if(check2(mid))
            rr = mid;
        else
            ll = mid;
    }
    cout << rr - r;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}