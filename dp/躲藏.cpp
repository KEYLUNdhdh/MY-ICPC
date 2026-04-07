#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 2000120420010122;
signed main()
{
    string s;
    while (cin >> s)
    {
        int cntc = 0, cntb = 0, cntw = 0, cntcc = 0;
        int i = 0;
        int ans = 0;
        while(i < s.size())
        {

            if(s[i] == 'c' || s[i] == 'C')
            {
                cntcc = (cntcc + cntb) % MOD;
                cntc = (cntc + 1) % MOD;
                i++;
            }
            else if(s[i] == 'w' || s[i] == 'W')
            {
                cntw = (cntw + cntc) % MOD;
                i++;
            }
            else if(s[i] == 'b' || s[i] == 'B')
            {
                cntb = (cntw + cntb) % MOD;
                i++;
            }
            else
                i++;
        }
        cout << cntcc % MOD << "\n";
    }
}