#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
struct DSU
{
    vector<int> f, siz;
    vector<pii> his;
    int part;
    DSU() {}
    DSU(int n)
    {
        init(n);
    }
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        his.clear();
        part = n;
    }
    int find(int x)
    {
        while(x != f[x])
            x = f[x];
        return x;
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(siz[x] < siz[y])
            swap(x, y);
        his.push_back({y, x});
        siz[x] += siz[y];
        f[y] = x;
        part--;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
    void undo()
    {
        if(his.empty())
            return;
        auto [y, x] = his.back();
        his.pop_back();
        siz[x] -= siz[y];
        f[y] = y;
        part++;
    }
    int hissize()
    {
        return his.size();
    }
    void rollback(int tag)
    {
        while(his.size() > tag)
            undo();
    }
};