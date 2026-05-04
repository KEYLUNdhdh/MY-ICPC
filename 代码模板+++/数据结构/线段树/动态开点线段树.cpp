#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct DynamicSegmentTree
{
    i64 maxVal, offsetValue, rootNode;
    vector<i64> ls, rs, sum;
    DynamicSegmentTree(i64 maxVal_= 2e7 + 5, i64 offset = 1e7 + 1)
    {
        maxVal = maxVal_;
        offset = offsetValue;
        rootNode = 0;

        ls.assign(1, 0);
        rs.assign(1, 0);
        sum.assign(1, 0);
    }

    i64 newNode()
    {
        ls.push_back(0);
        rs.push_back(0);
        sum.push_back(0);
        return ls.size() - 1;
    }

    void update(i64 &u, int l, int r, i64 val, i64 cnt)
    {
        if(!u)
            u = newNode();
        sum[u] += cnt;
        if(l == r)
            return;
        int m = l + r >> 1;
        if(val <= m)
            update(ls[u], l, m, val, cnt);
        else
            update(rs[u], m + 1, r, val, cnt);
    }

    i64 getRnk(i64 u, int l, int r, i64 val)
    {
        if(!u)
            return 1;
        if(l == r)
            return 1;
        int m = l + r >> 1;
        if(val <= m)
            return getRnk(ls[u], l, m, val);
        else
            return sum[ls[u]] + getRnk(rs[u], m + 1, r, val);
    }

    i64 getKth(i64 u, int l, int r, i64 k)
    {
        if(l == r)
            return l;
        int m = l + r >> 1;
        int lc = sum[ls[u]];
        if(k <= lc)
            return getKth(ls[u], l, m, k);
        else
            return getKth(rs[u], m + 1, r, k - lc);
    }

    void insert(i64 x)
    {
        update(rootNode, 1, maxVal, x + offsetValue, 1);
    }

    void remove(i64 x)
    {
        update(rootNode, 1, maxVal, x + offsetValue, -1);
    }

    i64 rank(i64 x)
    {
        return getRnk(rootNode, 1, maxVal, x + offsetValue);
    }

    i64 kth(i64 x)
    {
        return getKth(rootNode, 1, maxVal, x) -  offsetValue;
    }

    i64 prev(i64 x)
    {
        return (kth(rank(x) - 1));
    }

    i64 nxt(i64 x)
    {
        return (kth(rank(x + 1)));
    }
};