#include <iostream>
using namespace std;
int cnt = 1;
int a[5005][1100] = {
    {0},
    {1},
    {2}
};

void add(int k)
{
    int g = 0;
    for (int i = 0; i < cnt + 2;i++)
    {
        a[k][i] += a[k - 1][i] + a[k - 2][i] + g;
        g = a[k][i] / 10;
        a[k][i] %= 10;
    }
    for (int i = cnt + 1; i >= 0;i--)
    {
        if (a[k][i] != 0)
            {
                cnt = i;
                break;
            }
    }
}
int main()
{
    int n;
    cin >> n;
    if (n == 1)
        {
            cout << 1;
            return 0;
        }
    if (n == 2)
        {
            cout << 2;
            return 0;
        }
    for (int i = 3; i <= n;i++)
    {
        add(i);
    }
    for (int i = cnt; i >= 0;i--)
    {
        cout << a[n][i];
    }
}