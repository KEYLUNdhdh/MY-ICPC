#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e4 + 5;
int fa[MAXN << 1];
inline int Find(int x)
{
    if(fa[x] == x)
        return x;
    else
        return fa[x] = Find(fa[x]);
}

inline void unite(int x,int y)
{
    int fx = Find(x);
    int fy = Find(y);
    if(fx != fy)
    {
        fa[fx] = fy;
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= 2 * n;i++)
    {
        fa[i] = i;
    }
    char ch;
    int x, y;
    while(m--)
    {
        cin >> ch >> x >> y;
        if(ch == 'E')
        {
            unite(x, y + n);
            unite(y, x + n);
        }
        else
        {
            unite(x, y);
            //题目只说了“朋友的朋友是朋友”，并没有说“朋友的敌人也是共同的敌人”。
            // unite(x + n, y + n);
        }
    }
    map<int, int> mp;
    for (int i = 1; i <=n;i++)
    {
        mp[Find(i)]++;
    }
    cout << mp.size();
}