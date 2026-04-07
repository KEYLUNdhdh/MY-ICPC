#include <bits/stdc++.h>
using namespace std;
int a[1005] = {0};
// int  count(int n)
// {
//     int cnt = 0;
//     if (n == 1)
//         return 1;
//     for (int i = 1; i <= n / 2;i++)
//     {
//         cnt += count(i);
//     }
//     cnt++;
//     return cnt;
// }
void count(int n)
{
    for (int k = 2; k <= n + 1;k++)
    {
        for (int i = 1; i <= k / 2;i++)
        {
            a[k] += a[i];
        }
        a[k] += 1;
    }
}
int main()
{
    int n;
    cin >> n;
    a[1] = 1;
    count(n);
    cout << a[n];
}