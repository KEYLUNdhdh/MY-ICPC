#include <bits/stdc++.h>
using namespace std;
int x, y, cnt;
int main()
{
    cin >> x >> y;
    int tp = x * y;
    for (int k = 1; k * x <= x * y;k++)
    {
        int i = k * x;
        if(tp % i != 0)
            continue;
        int j = tp / i;
        if(gcd(i,j) == x)
            cnt++;
    }
    cout << cnt;
}