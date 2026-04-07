#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b, h;
    cin >> a >> b >> h;
    int cnt = 0;
    int sum = 0;
    while(sum < h)
    {
        sum += a;
        cnt++;
        if(sum >= h)
            break;
        sum -= b;
    }
    cout << cnt;
}