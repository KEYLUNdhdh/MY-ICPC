#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> f, siz, d;
    int mod;

    DSU(int n,int mod_) : f(n + 1), siz(n + 1, 1), d(n + 1, 0), mod(mod_)
    {
        iota(f.begin(), f.end(), 0);
    }
    int find(int x)
    {
        if (x != f[x])
        {
            int root = find(f[x]);
            d[x] = (d[x] + d[f[x]] + mod) % mod;
            f[x] = root;
        }
        return f[x];
    }
    bool merge(int x,int y,int v)
    {
        int rootx = find(x);
        int rooty = find(y);
        if(rootx == rooty)
        {
            int check = (d[x] - d[y] + mod) % mod;
            return check == v;
        }
        if(siz[rootx] < siz[rooty])
        {
            swap(rootx, rooty);
            v = (mod - v) % mod;
            swap(x, y);
        }
        f[rooty] = rootx;
        siz[rootx] += siz[rooty];
        d[rooty] = (d[x] - d[y] - v + mod) % mod;
        return true;
    }
    //求x -> y
    int query(int x,int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if(rootx != rooty)
            return -1;
        return (d[x] - d[y] + mod) % mod;
    }
};