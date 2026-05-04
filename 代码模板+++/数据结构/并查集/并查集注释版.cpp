#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct DSU
{
    vector<int> f, siz;
    DSU() {};
    DSU(int n)
    {
        init(n);
    }
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);//用连续递增的值填充一个范围//从第一个迭代器开始0, 1, 2, 3, ..., n-1
        siz.assign(n + 1, 1);
    }
    //这里的路径压缩只压缩了一半，每次调用路径减半，也是高效的做法
    //但在 99% 的题目中，这个和递归的Find没有体感上的区别。
    int find(int x)
    {
        while(x != f[x])
            x = f[x] = f[f[x]];
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
        // 按照 size 大小合并（启发式合并），保证树的高度平衡
        if(siz[x] < siz[y])
            swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};