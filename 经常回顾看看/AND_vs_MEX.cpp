#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using i32 = int;
signed main()
{
    i128 as;
    i64 t;
    cin >> t;
    while(t--)
    {
        i64 l, r;
        cin >> l >> r;
        i64 ll = __lg(l);
        i64 rr = __lg(r);
        if(ll == -1)
        {
            cout << r + 1 << "\n";
        }
        else if(ll == rr)
        {
            cout << 0 << "\n";
        }
        else if (rr - ll >= 2)
        {
            cout << r + 1 << "\n";
        }
        else
        {
            i64 ans = r - (1ll << rr) + 1;
            i64 low = 0;
            for (i64 j = ll; j >= 0;j--)
            {
                if((l >> j & 1) == 0)
                    break;
                else
                {
                    low |= 1ll << j;
                }
            }
            if(low <= ans)
                ans = r + 1;
            cout << ans << "\n";
        }
    }
}