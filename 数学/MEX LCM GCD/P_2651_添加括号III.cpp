#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        int mul = 1, di, tp,f = 0;
        for (int i = 1; i <= n;i++)
        {
            if(i == 2)
            {
                cin >> di;
                int gcc = gcd(mul, di);
                mul /= gcc;
                di /= gcc;
                if(di == 1)
                    f = 1;
            }
            else
            {
                if(i == 1)
                {
                    cin >> tp;
                    mul *= tp;
                }
                else
                {
                    cin >> tp;
                    int gcc = gcd(tp, di);
                    tp /= gcc;
                    di /= gcc;
                    if(di == 1)
                        f = 1;
                    // if(mul % di == 0)
                    // {
                    //     f = 1;
                    // }
                    // else
                    // {
                    //     mul %= di;
                    // }
                }
            }
        }
        if(f)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}