#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, k;
ll a[1005] = {0};

bool check(ll p)
{
    for (int i = 0; i < n;i++)
    {
        bool flag = 0;
        ll cost = 0;
        for (int j = i; j < n;j++)
        {
            ll need = p + i - j;
            if (a[j] >= need)
            {
                flag = 1;
                break;
            }
            if(j == n -1)
            {
                cost = k + 1;
                break;
            }
            cost += need - a[j];
            if (cost > k)
                break;
        }
        if(flag && cost <= k)
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        ll maxx = 0;
        for (int i = 0; i < n;i++)
        {
            cin >> a[i];
            maxx = max(maxx, a[i]);
        }
        ll l = 0;
        ll r = maxx + k + 1;
        while (l + 1 != r)
        {
            ll mid = l + r >> 1;
            if (check(mid))
                l = mid;
            else
                r = mid;
        }
        cout << l << "\n";
    }
    return 0;
}