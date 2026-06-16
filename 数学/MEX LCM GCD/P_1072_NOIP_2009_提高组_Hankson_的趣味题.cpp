#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    while(n--)
    {
        vector<int> vec;
        int a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;
        for (int i = 1; i * i <= b1;i++)
        {
            if(b1 % i == 0)
            {
                int r = b1 / i;
                vec.push_back(i);
                if(r != i)
                    vec.push_back(r);
            }
        }
        int cnt = 0;
        for(auto i : vec)
        {
            if(gcd(i,a0) == a1 && i * b0 == gcd(i,b0)  * b1)
                cnt++;
        }
        cout << cnt << "\n";
    }
}