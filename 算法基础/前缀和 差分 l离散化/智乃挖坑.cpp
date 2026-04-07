#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
//p f
void solve()
{
    i64 n, m, h;
    cin >> n >> m >> h;
    vector<pll> cao(m + 1);
    vector<i64> dis;
    for (int i = 1; i <= m;i++)
        cin >> cao[i].first >> cao[i].second;
    auto check = [&](int x) -> bool
    {
        debug(x);
        i64 ek = 0, eval = 0;
        //ek记录所有 < 1 的修改对位置 1 的斜率贡献,即当前斜率，一阶差分
        //eval记录所有 < 1 的修改对位置 1 的高度贡献，原数组
        dis.assign(n + 2, 0ll);
        for (int i = 1; i <= x;i++)
        {
            i64 p = cao[i].first, f = cao[i].second;
            i64 lw = p + 1 - f;
            i64 cen = p + 1;// > 1
            i64 up = p + 1 + f;
            //1 - index
            if(lw >= 1 && lw <= n)
            {
                dis[lw]++;
            }
            else if(lw < 1)
            {
                ek += 1;//因为坡是从左边开始的，所以传导到第 0 天时，斜率已经增加了 1。
                eval += (1 - lw);//这是计算第 0 天的高度。
                //公式含义：基础高度(1) + 从lw走到0走的步数(-lw)。
            }
            dis[cen] -= 2;
            if(up <= n)
            {
                dis[up]++;
            }
            
        }
        // debugarr(dis);
        // for (int i = 1; i <= n;i++)
        //     dis[i] = dis[i - 1] + dis[i];
        // debugarr(dis);
        // for (int i = 1; i <= n;i++)
        // {
        //     dis[i] = dis[i - 1] + dis[i];
        // }
        // debugarr(dis);
        // for (int i = 1; i <= n;i++)
        // {
        //     if(dis[i] > h)
        //     {
        //         dis.clear();
        //         return false;
        //     }
        // }
        
        for (int i = 1; i <= n;i++)
        {
            ek += dis[i];// 二阶差分 -> 一阶差分
            eval += ek; // 一阶差分 -> 原值
            if(eval > h)
            {
                dis.clear();
                return false;
            }
        }
        dis.clear();
        return true;
    };
    i64 l = 0, r = m + 1;
    debug(l);
    debug(r);
    while(l + 1 < r)
    {
        i64 mid = l + (r - l) / 2;
        if(check(mid))
            l = mid;
        else
            r = mid;
    }
    if(l == m)
        cout << "No";
    else
        cout << "Yes\n" << r;
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