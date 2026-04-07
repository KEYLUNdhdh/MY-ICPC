#include <bits/stdc++.h>
using namespace std;
int n, ans;
int f[114514];
//直接上代码，对p条直线分情况讨论平行线的条数，已知在有r条平行线时有（p-r）条线与他们相交于p*（p-r）个交点，再加上对于这p-r个交点的相交组合即可！！！
//f[m] 统计点的个数m之前是否出现过
void su(int p,int m)
{
    if(p == 0)
    {
        if(!f[m])
        {
            ans++;
            f[m] = 1;
        }
        return;
    }
    else
    {
        for (int r = p; r >= 1;r--)
        {
            su(p - r, r * (p - r) + m);
        }
    }
}
int main()
{
    cin >> n;
    su(n, 0);
    cout << ans;
}