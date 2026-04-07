#include <iostream>
#define int long long
using namespace std;

signed main()
{
    int n;
    cin >> n;
    double l = 0.0;
    double r = (double)n;
    while (r - l >= 0.1)
    {
        double mid = (r + l) / 2.0;
        if (mid * mid * mid >= n)
            r = mid;
        else
            l = mid;
    }
    cout << (int) r;
}