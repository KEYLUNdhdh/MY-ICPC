#include <iostream>
using namespace std;
#define int long long
#define len (int)(1e6+5)
int a[len] = {0};
int n,m;
inline int read()
{
    char ch;
    ch = getchar();
    int x = 0;
    while (ch <'0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
// inline void out(int x)
// {
//     if (x < 0)
//         putchar('-'), x = -x;
//     if (x < 10)
//         putchar(x + '0');
//     else
//         out(x / 10), putchar(x % 10 + '0');
// }
int search(int x)
{
    int l = 0;
    int r = n + 1;
    while (l + 1 != r)
    {
        int mid = l + (r - l) / 2;
        if (a[mid] < x)
            l = mid;
        else
            r = mid;
    }
    if (a[r] == x)
        return r;
    else
        return -1;
}
signed main()
{
    n = read();
    m = read();
    for (int i = 1; i <= n;i++)
        a[i] = read();
    while(m--)
    {
        int tp = read();
        int ans = search(tp);
        printf("%d ",ans);
    }
}