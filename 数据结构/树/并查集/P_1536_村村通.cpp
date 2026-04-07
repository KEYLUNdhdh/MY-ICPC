#include <bits/stdc++.h>
using namespace std;
vector<int> vec;
int fa[2000];

int Find(int x)
{
    if (x == fa[x])
        return x;
    else
        return fa[x] = Find(fa[x]);
}

int main()
{
    int n, m;
    while(cin >> n >> m)
    {
        for (int i = 1; i <= n;i++)
        {
            fa[i] = i;
        }
        int u,v;
        while(m--)
        {
            cin >> u >> v;
            int ua = Find(u);
            int uv = Find(v);
            if(ua != uv)
            {
                fa[ua] = uv;
            }
        }
        for (int i = 1; i <= n;i++)
        {
            Find(i);
        }
        map<int, int> mp;
        for (int i = 1; i <= n;i++)
        {
            mp[fa[i]]++;
        }
        cout << mp.size() - 1 << "\n";
    }
}