#include <bits/stdc++.h>
#define int long long
using namespace std;
int hashe(char c1,char c2)
{
    return (c1 - 'A') * 26 + (c2 - 'A');
}
int res[1000][1000];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    string s, q, tp;
    int ans = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> s >> q;
        int state = hashe(q[0], q[1]);
        int city = hashe(s[0], s[1]);
        // 题目要求：来自不同的州
        // 如果前缀和州名完全一样（比如 TEXAS TX），无法构成特殊对，直接跳过
        if(state != city)
        {
            // 我们是 (州S, 前缀P)
            // 我们要找之前出现过的 (州P, 前缀S)
            ans += res[state][city];
            res[city][state]++;
        }
    }
    cout << ans;
}