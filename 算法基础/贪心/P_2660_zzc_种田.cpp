#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int a, b;
    cin >> a >> b;
    int ans = 0;
    while((a > 1 && b > 1))
    {
        if(a == b)
        {
            break;
        }
        if (a > b)
            swap(a, b);
        int kuai = b / a;
        b = b - a * kuai;
        ans += a * 4 * kuai;
    }
    if(a > b)
        swap(a, b);
    if(a == b)
        ans += a * 4;
    else if(a == 0 || b == 0)
        ;
    else
        ans += b / a * 4;
    cout << ans;
}