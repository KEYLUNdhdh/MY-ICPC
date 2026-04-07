#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll mod = 1e9 + 7;
int a[100005] = {0};

int main()
{
    int minn = 0x3f3f3f3f;
    int maxx = 0;
    int n;
    cin >> n;
    int tp;
    for (int i = 0; i < n;i++)
    {
        cin >> tp;
        a[tp]++;
        minn = min(minn, tp);
        maxx = max(maxx, tp);
    }
    ll ans = 0;
    for (int i = minn + 1; i <= maxx;i++)
    {
        if(a[i] >= 2)
        {
            for (int j = minn; j <= i / 2;j++)
            {
                if (j != i - j)
                    ans += a[i] * (a[i] - 1) * a[j] * a[i - j] / 2 % mod;
                else if (a[j] >= 2 && 2*j == i)
                    ans += a[i] * (a[i] - 1) * a[j] * (a[j] - 1) / 4 % mod;
            }
            ans %= mod;
        }
    }
    cout << ans;
}