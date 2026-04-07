#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;

void solve()
{
    string s;
    cin >> s;
    auto check = [&](char sb, char now)
    {
        int op = now - '0';
        if(op == 0)
        {
            return ('0' + '3' - sb);
        }
        else if(op == 1)
        {
            int sw = ('4' - sb) % 4;
            return sw + '0';
        }
        else if(op == 2)
        {
            int sw = sb - '0';
            if(sw >= 2)
            {
                int d = (sw - 2) ^ 1;
                return (2 + d + '0');
            }
            else
                return (sw ^ 1 + '0');
        }
        else if(op == 3)
        {
            if((sb - '0') % 2 == 0)
            {
                if(sb == '0')
                    return (int)'2';
                else
                    return (int)'0';
            }   
            else
                return (int)sb;
        }
        else if(op == 4)
        {
            int sw = sb - '0';
            return ('0' + (sw + 1) % 4);
        }
        else
        {
            int sw = sb - '0';
            return ('0' + (sw - 1 + 4) % 4);
        }
    };
    string ans = "0";
    for (int i = 0; i < s.size();i++)
    {
        ans.push_back((char)check(ans.back(), s[i]));
    }
    cout << ans.substr(1);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}