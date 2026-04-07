//nowcoder
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using i32 = int;
i64 l, r;
i64 rev(i64 x)
{
    i64 res = 0;
    i64 tp = x;
    while(tp)
    {
        res = res * 10 + tp % 10;
        tp /= 10;
    }
    return res;
}
signed main()
{
    i64 t;
    cin >> t;
    while(t--)
    {
        cin >> l >> r;
        i64 ori = r;
        if(r < 9)
        {
            cout << r << "\n";
            continue;
        }
        i64 maxx = rev(r);
        i64 p = 10;
        while(1)
        {
            i64 hou = (r / p) * p - 1;
            if(hou < l)
                break;
            else
            {
                maxx = max(maxx, rev(hou));
                if(p * 10 > r)
                    break;
                else
                    p *= 10;
            }
        }
        cout <<  maxx << "\n";
    }
}