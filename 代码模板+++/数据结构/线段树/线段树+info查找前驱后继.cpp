#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<class Info>
struct SegmentTree
{
    int n;
    vector<Info> info;
    SegmentTree() : n{0} {}
    SegmentTree(int n_,Info v_ = Info())
    {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(vector<T> init_)
    {
        init(init_);
    }
    void init(int n_,Info v_ = Info())
    {
        init(vector(n_, v_));
    }
    template<class T>
    //**init start from 0 - index**
    //**SegmentTree start from 1 - index**
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 * n + 1, Info());
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if(r == l)
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
        //oprator+
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p,int l,int r,int x,const Info &v)
    {
        if(r == l)
        {
            info[p] = v;
            return;
        }
        int m = l + (r - l) / 2;
        if(x <= m)
        {
            modify(2 * p, l, m, x, v);
        }
        else
        {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int p,const Info &v)
    {
        modify(1, 1, n, p, v);
    }
    Info rangeQuery(int p,int l,int r,int x,int y)
    {
        //assume that Info x + Info() = x
        //need to keep an eye on operator+
        if(l > y || r < x)
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
    int findFirst(int p,int l,int r ,int x,int y,F pred)
    {
        if(l > y || r < x || !pred(info[p]))
            return -1;
        if(r == l)
        {
            return l;
        }
        int m = l + (r - l) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if(res == -1)
            res = findFirst(2 * p + 1, m + 1, r, x, y, pred);
        return res;
    }
    template<class F>
    int findFirst(int x,int y,F pred)
    {
        return findFirst(1, 1, n, x, y, pred);
    }
    template<class F>
    int findLast(int p,int l,int r,int x,int y,F pred)
    {
        if(l > y || r < x || !pred(info[p]))
            return -1;
        if(r == l)
            return l;
        int m = l + (r - l) / 2;
        int res = findLast(2 * p + 1, m + 1, r, x, y, pred);
        if (res == -1)
            res = findLast(2 * p, l, m, x, y, pred);
        return res;
    }
    template<class F>
    int findLast(int x,int y,F pred)
    {
        return findLast(1, 1, n, x, y, pred);
    }
};
//Info could be modified according to the subject
//可嫁接
struct Info
{
    //....
};

//Info operator+(Info a,Info b)...//necessary
//Info operator-....