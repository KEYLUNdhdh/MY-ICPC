#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k;
bool check(int p)
{
    if (n > k)
    {
        int mul = (n + k  -1)/ k;
        int tp = k * (mul);
        return p * n >= tp;
    }
    return p * n >= k;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        int l = 0;
        int r = k + 1;
        while (l + 1 != r)
        {
            int mid = l + r >> 1;
            if (check(mid))
                r = mid;
            else
                l = mid;
        }
        cout << r << "\n";
    }
}