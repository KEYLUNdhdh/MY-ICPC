#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1000010] = {0};
int n, m;
int sum1(int h)//计算h下能获得多少木材
{
    int sum = 0;
    // for (int i = n - 1; i >= 0;i++)
    // {
    //     if (a[i] > h)
    //     {
    //         sum += a[i] - h;
    //     } 
    //     else
    //     {
    //         break;
    //     }
    // }
    for (int i = 0; i < n;i++)
    {
        if (a[i] > h)
        {
            sum += a[i] - h;
        }
    }
        return sum;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int sum = 0;
    cin >> n >> m;
    for (int i = 0; i < n;i++)
        cin >> a[i];
    sort(a, a + n);
    // int l = n - 1;
    // int r = n - 1;
    // // 特判n == 1;
    // if (n == 1)
    // {
    //     cout << a[0] - m;
    //     return 0;
    // }
    // //n 至少为2 同时考虑l索引到 0 的情况
    // else
    // {
    //     l = search(a[n - 1]);
    //     sum += (n - l) * a[n - 1];
    //     int h = a[l - 1];
    //     while (l != 0 && (sum - (n - l) * h) < m)
    //     {
    //         r = l - 1;
    //         l = search(h);
    //         sum += (r - l + 1) * h;
    //         h = a[l - 1];
    //     }
    //     if (l == 0 && sum - (n - l) * h < m)
    //     {

    //         int del = (m - (sum - (n - l) * h)) / n;
    //         h -= (del + 1);
    //     }
    //     else//h向上查找的过程
    //     {
    //         int surpass = sum - (n - l) * h - m;
    //         int del = surpass / (n - l);
    //         h += del + 1;
    //     }
    //     cout << h;
    // }
    int l = -1;
    int r = a[n - 1]+ 1;
    while (l + 1 != r)
    {
        int mid = l + r >> 1;
        if (sum1(mid) >= m)
            l = mid;
        else
            r = mid;
    }
    cout << l;
}