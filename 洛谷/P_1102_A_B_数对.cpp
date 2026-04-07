#include <iostream>
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[300005] = {0};
int n, c;
// int binary_search(int a[],int left,int right,int x)
// {
//     if (left > right)
//         return 0;
//     int mid = (left + right) / 2;
//     if (a[mid] == x)
//         return 1;
//     else if (a[mid] > x)
//         return binary_search(a, left, mid - 1, x);
//     else
//         return binary_search(a, mid + 1, right, x);
// }
int search1(int x) //返回最左边索引
{
    int l = -1;
    int r = n;
    while(l + 1 != r)
    {
        int mid = l + r >> 1;
        if(a[mid] < x)
            l = mid;
        else
            r = mid;
    }
    if (a[r] == x)
        return r;
    else
        return -1;
}

int search2(int x)// 返回最右边索引
{
    int l = -1;
    int r = n;
    while (l + 1 != r)
    {
        int mid = l + r >> 1;
        if (a[mid] <= x)
            l = mid;
        else
            r = mid;
    }
    if (a[l] == x)
        return l;
    else
        return -1;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin >> n >> c;
    for (int i = 0; i < n;i++)
        cin >> a[i];
    int cnt = 0;
    sort(a, a + n);
    for (int i = 0; i < n;i++)
    {
        int tp = a[i] + c;
        int l = search1(tp);
        int r = search2(tp);
        if (l != -1 && r != -1)
            cnt += r - l + 1;
    }
    cout << cnt;
}