#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
typedef struct p{
    int x, y;
    char f;
}p;
// 最早出现向右
//最晚出现向左
unordered_map<int, int> mp;
p po[N] = {0};
// int r[N] = {0};//对每一行，最早👉
// int l[N] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin >> n;
    // for (int i = 0; i < n;i++)
    // {
    //     r[i] = 0x3f3f3f3f;
    //     l[i] = -1;
    // }
    for (int i = 0; i < n; i++)
    {
        cin >> po[i].x >> po[i].y;
    }
    cin >> s;
    for (int i = 0; i < n;i++)
    {
        po[i].f = s[i];
    }
    sort(po, po + n, [](p p1, p p2)
         { return p1.y < p2.y; });
    int lp = 0;
    int pos = 0;
    int l = -1, r = 0x3f3f3f3f;
    while(pos != n)
    {
        if(po[pos].y != po[lp].y)
        {
            lp = pos;
            r = 0x3f3f3f3f;
            l = -1;
            continue;
        }
        if(po[pos].f == 'R')
            r = min(r, po[pos].x);
        else
            l = max(l, po[pos].x);
        if(r <= l)
        {
            cout << "Yes";
            return 0;
        }
        pos++;
    }
    cout << "No";
    return 0;
    // for (int i = 0; i < n;i++)
    // {
    //     // if(po[i].f == 'R')
    //     // {
    //     //     r[po[i].y] = min(r[po[i].y], po[i].x);
    //     // }
    //     // else
    //     // {
    //     //     l[po[i].y] = max(l[po[i].y], po[i].x);
    //     // }
    //     if(po[i].f == 'R')
    //     {
    //         if(mp[po[i].y] != 0)
    //         {

    //         }
    //     }
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     if (r[i] <= l[i])
    //     {
    //         cout << "Yes";
    //         return 0;
    //     }
    //     }
    // cout << "No";
    // return 0;
}   