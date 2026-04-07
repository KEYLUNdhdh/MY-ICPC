#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[100010] = {0};
int l, n, k;
//最大的最小
bool check(int p)//判断当前路障是否够用
{
    int cnt = 0;
    for (int i = 1; i <= n + 1;i++)
    {
        if (a[i] - a[i - 1] >p)
        {
            int tp = (a[i] - a[i - 1] + p - 1) / p - 1;
            cnt += tp;
        }
    }
    return cnt <= k;
}

signed main()
{
    cin >> l >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    a[n + 1] = l;
    int left = 0;
    int right = l + 1;
    while (left + 1 != right)
    {
        int mid = left + right >> 1;
        if (check(mid))
            right = mid;
        else
            left = mid;
    }
    cout << right;
}