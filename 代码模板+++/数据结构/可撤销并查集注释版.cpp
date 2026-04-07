#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
struct DSU
{
    vector<int> f, siz;
    vector<pii> his;//记录历史操作,[y, x]表示y成为了x的儿子
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
    //路径压缩解除了
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
    // 新增：撤销上一次成功的 merge 操作
    void undo()
    {
        if(his.empty())
            return;
        // 取出栈顶：y 是子节点，x 是父节点
        auto [y, x] = his.back();
        his.pop_back();
        // 还原操作
        siz[x] -= siz[y];
        f[y] = y;
        part++;
    }
    // 新增：获取当前状态（快照）
    int hissize()
    {
        return his.size();
    }
    // 新增：回滚到之前的某个快照状态
    void rollback(int tag)
    {
        while(his.size() > tag)
            undo();
    }
};