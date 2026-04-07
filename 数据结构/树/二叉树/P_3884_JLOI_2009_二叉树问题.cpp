#include <bits/stdc++.h>
using namespace std;
int n;
const int MAXN = 200;
int fa[MAXN];
int deep[MAXN];
int width[MAXN];
vector<int> children[MAXN];
int maxdeep,maxwidth;

void dfs(int u,int d)
{
    deep[u] = d;
    width[d]++;
    if(d > maxdeep)
        maxdeep = d;
    for(int v : children[u])
        dfs(v, d + 1);
}

int getlca(int u,int v)
{
    while(deep[u] > deep[v])
        u = fa[u];
    while(deep[v] > deep[u])
        v = fa[v];
    while(1)
    {
        if(u == v)
            return u;
        else
        {
            u = fa[u];
            v = fa[v];
        }
    }
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    int u, v;
    for (int i = 1; i < n;i++)
    {
        cin >> u >> v;
        fa[v] = u;
        children[u].push_back(v);
    }
    dfs(1, 1);
    for (int i = 1; i < n;i++)
    {
        maxdeep = max(maxdeep, deep[i]);
    }
    for (int i = 1; i <= n;i++)
    {
        maxwidth = max(maxwidth, width[i]);
    }
    int x, y;
    cin >> x >> y;
    int faa = getlca(x, y);
    int ans = (deep[faa] - deep[x]) * 2 + (deep[faa] - deep[y]);
    ans = -ans;
    cout << maxdeep << "\n"
         << maxwidth << "\n"
         << ans;
}