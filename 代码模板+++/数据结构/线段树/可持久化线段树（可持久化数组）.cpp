#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SegmentTree
{
    struct Node
    {
        int ls, rs;
        int val;
    };

    int n;
    vector<Node> tr;
    vector<int> root;

    SegmentTree(int n_, const vector<int> &a) : n(n_)
    {
        // 预分配足够的空间：N + M * ceil(log2(N))
        tr.reserve(25000005);
        tr.push_back({0, 0, 0});
        root.push_back(build(1, n, a));
    }

    int cloneNode(int u)
    {
        tr.push_back(tr[u]);
        return tr.size() - 1;
    }

    // 1 - index
    int build(int l, int r, const vector<int> &a)
    {
        int u = tr.size();
        tr.push_back({0, 0, 0});
        if(l == r)
        {
            tr[u].val = a[l];
            return u;
        }
        int mid = l + (r - l) / 2;
        tr[u].ls = build(l, mid, a);
        tr[u].rs = build(mid + 1, r, a);
        return u;
    }

    int update(int prev_rt, int l, int r, int pos, int val)
    {
        int u = cloneNode(prev_rt);
        if(l == r)
        {
            tr[u].val = val;
            return u;
        }
        int mid = l + (r - l) / 2;
        if(pos <= mid)
            tr[u].ls = update(tr[prev_rt].ls, l, mid, pos, val);
        else
            tr[u].rs = update(tr[prev_rt].rs, mid + 1, r, pos, val);
        return u;
    }

    int query(int rt, int l, int r, int pos)
    {
        if(l == r)
            return tr[rt].val;
        int mid = l + (r - l) / 2;
        if(pos <= mid)
            return query(tr[rt].ls, l, mid, pos);
        else
            return query(tr[rt].rs, mid + 1, r, pos);
    }
};