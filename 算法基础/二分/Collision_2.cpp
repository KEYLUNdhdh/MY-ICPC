#include<iostream>
using namespace std;
#define int long long
int a[1000005] = {0};
inline int read()
{
    char ch;
    int f = 1;
    int x = 0;
    ch = getchar();
    while (ch < '0' && ch >'9')
    {
        if (ch == '-')
        {
            f = -1;
            ch = getchar();
        }
    }
    while(ch >='0' && ch <='9')
    {
        x = x * 10 + (ch - '0');
    }
    return x * f;
}
inline void out(int x)
{
    char ch;
    if (x < 0)
        putchar('-'), x = -x;
    if (x < 10)
        putchar(x + '0');
    if (x >= 10)
        out(x / 10), putchar(x % 10 + '0');
}
int search(int a[],int left,int right,int x)
{
    if (left > right)
        return -1;
    int mid = left + (right - left) / 2;
    if (a[mid] == x)
        return mid;
    else if (a[mid] < x)
        search(a, mid + 1, right, x);
    else
        search(a, left, mid - 1, x);
}

signed main()
{
    int n,m;
    n = read();
    m = read();
    int temp;
    for (int i = 0; i < n;++i)
    {
        temp = read();
        a[i] == temp;
    }
    int x;
    while (m--)
    {
        x = read();
        out(search(a, 0, n - 1, x));
        cout << "\n";
    }
}