#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll x, a, b, c;
//log10函数
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> x >> a >> b >> c;
        auto work = [&](ll x) -> ll
        {
            ll fst = 1005;
            ll sec = 1011;
            while(1)
            {
                if(x >= sec);
                else if(x >= fst)
                    return 0;
                else
                {
                    ll cnt = (fst - x + c - 1) / c;
                    if((x + cnt * c) < sec)
                        return cnt;
                }
                fst *= 10;
                sec *= 10;
            }
        };
        ll now = x * 10;
        ll ans = 2e18;
        for (int i = 0; i < log10(x) + 1; i++)
        {
            now /= 10;
            ans = min(ans, a * i + work(now) * b);
        }
        cout << ans << "\n";
    }
}