#include <iostream>
#include <iomanip>
#include <cmath>
#define int long long
using namespace std;


long double solve(int k,long double a,long double b,int x)
{
    //md递归调半天忘了会tle了，干
    // long double ans;
    // long double f = a * (long double)x;
    // long double g = (long double)x + b;
    // if (k == 0) 
    // {
    //     ans = (f + g)/2;
    //     return ans;
    // }
    // if (k >= 1)
    //     {
    //         ans = (a + 1) * solve(k - 1, a, b, x) / 2.0 + b / 2.0;
    //         return ans;
    //     }
    if (a == 1)
    {
        return (long double)x + (long double)x * (b / 2.0);
    }
    long double p = (long double)pow((a + 1)/2.0, k);
    long double res = (long double)p * (long double)x + (long double)b * (long double)(p - 1) / (long double)(a - 1);
    return res;
}

signed main()
{
    ios::sync_with_stdio(0);
    int n,m;
    long double a, b;
    cin >> a >> b >> n >> m;
    int x;
    while (n--)
    {
        cin >> x;
        long double res = solve(m, a, b, x);
        cout<< fixed << setprecision(9) << res;
        if (n != 0)
            cout << " ";
    }
}

