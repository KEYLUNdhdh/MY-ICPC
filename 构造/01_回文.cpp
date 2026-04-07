#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
//那如果矩阵有超过一个 1，那任意一个1  只要找到离他最近的  1的路径，就可以保证它们中间全都是 1，反之同理。
//很巧妙的想法
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> vec(n);
    int cnt0 = 0, cnt1 = 0;
    for (int i = 0; i < n;i++)
    {
        vec[i].assign(m, 0);
        for (int j = 0; j < m;j++)
        {
            cin >> vec[i][j];
            if(vec[i][j] == '0')
                cnt0++;
            else
                cnt1++;
        }
    }
    for (int i = 0; i < n;i++)
    {
        string s;
        for (int j = 0; j < m;j++)
        {
            if(vec[i][j] == '0')
            {
                s += (cnt0 > 1 ? "Y" : "N");
            }
            else
            {
                s += (cnt1 > 1 ? "Y" : "N");
            }
        }
        cout << s << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}