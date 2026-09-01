#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// 这里建的是权值线段树，val代表出现几次。
struct ChairmanTree
{
    struct Node
    {
        int ls, rs;
        int val;
    };

    int max_val;// 值域的 ub
    vector<Node> tr;
    vector<int> root;

    ChairmanTree(int M) : max_val(M)
    {
        tr.reserve(4000005);// N*log(N) 级别
        tr.push_back({0, 0, 0});
        root.push_back(0);
    }

    int cloneNode(int u)
    {
        tr.push_back(tr[u]);
        return tr.size() - 1;
    }

    int update(int prev_rt, int l, int r, int pos)
    {
        int u = cloneNode(prev_rt);
        tr[u].val++;

        if(l == r)
            return u;
        int mid = l + (r - l) / 2;
        if(pos <= mid)
            tr[u].ls = update(tr[prev_rt].ls, l, mid, pos);
        else
            tr[u].rs = update(tr[prev_rt].rs, mid + 1, r, pos);
        return u;
    }

    // v - u
    int query(int u, int v, int l, int r, int k)
    {
        if(l == r)
            return l;

        int lcnt = tr[tr[v].ls].val - tr[tr[u].ls].val;
        int mid = l + (r - l) / 2;
        if(k <= lcnt)
            return query(tr[u].ls, tr[v].ls, l, mid, k);
        else
            return query(tr[u].rs, tr[v].rs, mid + 1, r, k - lcnt);
    }
};