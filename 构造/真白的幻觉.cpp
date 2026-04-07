#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
//先编写程序模拟构造出来，在直接输出
void solve()
{
    // int maxcnt = 0;
    // vector<string> ava;

    // auto check = [&](string s)
    // {
    //     i64 num = 1;
    //     for (int i = 0; i < s.size();i++)
    //     {
    //         num *= s[i] - '0';
    //     }
    //     return to_string(num);
    // };
    // for (int i = 0; i <= 36;i++)//2
    // {
    //     for (int j = 0; j <= 36;j++)//3
    //     {
    //         for (int k = 0; k <= 36;k++)//7
    //         {
    //             string s;
    //             int eight = i / 3;
    //             int two = i % 2;
    //             int nine = j / 2;
    //             int three = j % 2;
    //             int six = min(two, three);
    //             two -= six, three -= six;
    //             s.append(two, '2');
    //             s.append(three, '3');
    //             s.append(six, '6');
    //             s.append(k, '7');
    //             s.append(eight, '8');
    //             s.append(nine, '9');
    //             if(s.size() > 18)
    //                 continue;
    //             int cnt = 0;
    //             string ori = s;
    //             while(s.size() > 1)
    //             {
    //                 s = check(s);
    //                 cnt++;
    //             }
    //             if(cnt > maxcnt)
    //             {
    //                 ava.clear();
    //                 maxcnt = cnt;
    //                 ava.push_back(ori);
    //             }
    //             else if(cnt == maxcnt)
    //             {
    //                 ava.push_back(ori);
    //             }
    //         }
    //     }
    // }
    // cout << maxcnt << "\n";
    // for(auto it : ava)
    //     cout << it << " ";
    cout << 27777789999999999 << " " << 277777788888899;
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