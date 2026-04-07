#include <bits/stdc++.h>
using namespace std;
int n, m, p;
const int MAXN = 5e3 + 5;
int fa[MAXN];
int Find(int x)
{
    if(fa[x] == x)
        return x;
    else
        return fa[x] = Find(fa[x]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> p;
    int u, v;
    for (int i = 1; i <= n;i++)
    {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v;
        int ua = Find(u);
        int uv = Find(v);
        if(ua != uv)
        {
            fa[ua] = uv;
        }
    }
    int x, y;
    while(p--)
    {
        cin >> x >> y;
        if(Find(x) == Find(y))
        {
            cout << "Yes\n";
        }
        else
            cout << "No\n";
    }     
}