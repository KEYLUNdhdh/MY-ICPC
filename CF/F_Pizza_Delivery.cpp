#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, ax, ay, bx, by;
const int MAXN = 2e5 + 5;
int x[MAXN], y[MAXN];
int dp[MAXN][2];
struct lst{
    int x;
    int maxy;
    int miny;
};
struct po{
    int x, y;
};
bool cmp(po p1,po p2)
{
    if(p1.x != p2.x)
        return p1.x < p2.x;
    else
        return p1.y < p2.y;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> ax >> ay >> bx >> by;
        int costx = abs(bx - ax);
        int minx = 0x3f3f3f3f, maxx = -0x3f3f3f3f;
        for (int i = 1; i <= n;i++)
        {
            cin >> x[i];
            minx = min(minx, x[i]);
            maxx = max(maxx, x[i]);
        }
        for (int i = 1; i <= n;i++)
            cin >> y[i];
        po tp;
        vector<po> vec;
        for (int i = 1; i <= n;i++)
        {
            tp.x = x[i], tp.y = y[i];
            vec.push_back(tp);
        }
        // po aa,bb;
        // aa.x = minx, aa.y = ay;
        // bb.x = maxx, bb.y = by;
        // vec.push_back(aa);
        // vec.push_back(bb);
        sort(vec.begin(), vec.end(), cmp);
        vec.push_back({0x3f3f3f3f, 0x3f3f3f3f});
        int prev = minx;
        vector<lst> res;
        lst oo;
        oo.miny = vec[0].y;
        for (int i = 0; i < vec.size();i++)
        {
            if(vec[i].x != prev)
            {
                oo.x = prev;
                oo.maxy = vec[i - 1].y;
                prev = vec[i].x;
                res.push_back(oo);
                oo.miny = vec[i].y;
            }
        }
        dp[0][0] = 0;
        dp[0][1] = 0;
        int lprev = ay;
        int rprev = ay;
        int index = 1;

        for(auto it : res)
        {
            //0
            int lcur = it.miny;
            int rcur = it.maxy;
            int cost = rcur - lcur;
            dp[index][0] = min(dp[index - 1][0] + abs(lprev - rcur), dp[index - 1][1] + abs(rprev - rcur)) + cost;
            dp[index][1] = min(dp[index - 1][0] + abs(lprev - lcur), dp[index - 1][1] + abs(rprev - lcur)) + cost;
            index++;
            lprev = lcur;
            rprev = rcur;
        }
        int cost1 = dp[index - 1][0] + abs(lprev - by);
        int cost2 = dp[index - 1][1] + abs(rprev - by);
        cout << min(cost1, cost2) + costx << "\n";
    }
}