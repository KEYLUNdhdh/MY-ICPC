#include <iostream>
#define int long long
using namespace std;
int n, m;
//二分 + 贪心
int a[100005] = {0};
int check(int p)
{
    int cnt = 0;
    int sum = 0;
    for (int i = 0; i < n;i++)
    {
        sum += a[i];
        if (sum <= p )
        {
            continue;
        }
        else
        {
            cnt++;
            sum = a[i];
        }
    }
    cnt = cnt + 1;
    return cnt > m;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m;
    int l = 0;
    int r = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        r += a[i];
        l = max(l, a[i]);
    }
    l -= 1;
    r += 1;
    while (l + 1 != r)
    {
        int mid = l + r >> 1;
        if (check(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    cout << r;
}