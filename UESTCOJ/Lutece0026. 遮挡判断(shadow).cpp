#include  <bits/stdc++.h>
#define int long long
using namespace std;
typedef struct pillar
{
    int x, h;
    int val;
} pp;
vector<pillar> p;
bool cop(pp p1,pp p2)
{
    return p1.x < p2.x;
}
void solve(int n)
{
    pp temp;
    p.resize(n);
    for (int i = 0; i < n;i++)
    {
        scanf("%lld %lld", &p[i].x, &p[i].h);
    }
    int t, a;
    scanf("%lld/%lld", &t, &a);
    sort(p.begin(), p.end(), cop);
    for (auto& it : p)
    {
        it.val = it.h * a + it.x * t;
    }
    int max_e = 0;
    int cnt = 0;
    for (int i = 0; i < n;i++)
    {
        if (p[i].val > max_e)
        {
            cnt++;
            max_e = p[i].val;
        }
    }
    printf("%d\n", cnt);
}

signed main()
{
    int n;
    while (scanf("%lld", &n) && n != 0)
    {
        solve(n);
    }
}