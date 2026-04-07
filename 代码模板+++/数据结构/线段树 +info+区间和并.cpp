#include  <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<class Info>
struct SegmentTree
{
    int n;
    vector<Info> info;
    SegmentTree()  : n{} {}
    SegmentTree(int n_,Info v_ =  Info())
    {
        init(n_, v_);
    }
    tmeplate<class T>
    SegmentTree(vector<T> init_)
    {
        init(init_);
    }
    void init(int n_,int v_)
    {
        init(vector(n_, v_));
    }
    //**init start from 0 - index**
    //**SegmentTree start from 1 - index**
    void init(vector<Info> init_)
    {
        int n = init_.size();
        info.assign(4 * n + 1, Info());
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if(l == r)
            {
                info[p] = init_[l - 1];
                return;
            }
            int m = l + (r - l) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }
    void pull(int p)
    {
        //operator+
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p,int l,int r,int x,const Info &v)
    {
        if(l == r)
        {
            info[p] = v;
            return;
        }
        int m = l + (r - l) / 2;
        if(x <= m)
            modify(2 * p, l, m, x, v);
        else
            modify(2 * p + 1, m + 1, r, x, v);
        pull(p);
    }
    Info rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x || !pred(indo[p]))
            return Info();
        if(l >= x && r <= y)
            return info[p];
        int m = l + (r - l) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }
    Info rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y);
    }
    template<class F>
    int findFirst
};