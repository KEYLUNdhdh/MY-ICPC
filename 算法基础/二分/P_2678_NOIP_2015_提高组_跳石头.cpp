#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[60000] = {0};
int l, n, m;
bool check(int p)//判断是否可行,数组从0 到 n + 1
{
    int cnt = 0;
    int prev = 0;//记录前一个索引
    for (int i = 1; i <= n + 1;i++)
    {
        if (a[i] - a[prev] < p)
        {
            cnt++;
        }
        else
        {
            prev = i;
        }
    }
    return cnt <= m;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin >> l >> n >> m;
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    a[n + 1] = l;
    int left = 0;
    int right = l + 1;
    while (left + 1 != right)
    {
        int mid = (left + right) >> 1;
        if (check(mid))
            left = mid;
        else
            right = mid;
    }
    cout << left;
}