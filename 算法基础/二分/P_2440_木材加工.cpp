#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, k;
int a[100005] = {0};
int su2(int len)
{
    int sum = 0;
    for (int i = 0; i < n;i++)
    {
        sum += a[i] / len;
    }
    return sum;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 0; i < n;i++)
        cin >> a[i];
    sort(a, a + n);

    int l = 0;
    int r = a[n - 1] + 1;
    while (l + 1 !=r)
    {
        int mid = l + r >> 1;
        if (su2(mid) >= k)
            l = mid;
        else
            r = mid;
    }
    cout << l;
}