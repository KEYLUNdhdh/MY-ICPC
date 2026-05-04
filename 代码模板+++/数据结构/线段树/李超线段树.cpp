#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;

struct Line
{
    db k, b;
    int id;
};

struct LiChaoTree
{
    int n;
    vector<int> tree;
    vector<Line> lines;
    LiChaoTree(int n_) : n(n_), tree(4 * n_ + 1, 0), lines(1, {0, 0, 0}) {}
    
    db calc(int id, int x)
    {
        if(!id)
            return 0;
        return lines[id].k * x + lines[id].b;
    }

    int cmp(db x, db y)
    {
        const db EPS = 1e-9;
        if(x - y > EPS)
            return 1;
        if(y - x > EPS)
            return -1;
        return 0;
    }

    void addLine(int x0, int y0, int x1, int y1, int id)
    {
        if(x0 > x1)
        {
            swap(x0, x1);
            swap(y0, y1);
        }

        db k, b;
        if(x0 == x1)
        {
            k = 0;
            b = max(y0, y1);
        }
        else
        {
            k = 1. * (y1 - y0) / (x1 - x0);
            b = y0 - k * x0;
        }
        lines.push_back({k, b, id});
        insert(1, 1, n, x0, x1, id);
    }

    void insert(int p, int l, int r,int x, int y, int u)
    {
        if(x <= l && r <= y)
        {
            int &v = tree[p];
            int m = l + r >> 1;
            if(!v)
            {
                v = u;
                return;
            }

            int fm = cmp(calc(u, m), calc(v, m));
            if(fm == 1 || (fm == 0 && u < v))
            {
                swap(u, v);
            }

            if(l == r || !u)
                return;
            
            int fl = cmp(calc(u, l), calc(v, l));
            if(fl == 1 || (fl == 0 && u < v))
                insert(p << 1, l, m, x, y, u);
            else
                insert(p << 1 | 1, m + 1, r, x, y, u);
            return;
        }
        int m = l + r >> 1;
        if(x <= m)
            insert(p << 1, l, m, x, y, u);
        if(y >= m + 1)
            insert(p << 1 | 1, m + 1, r, x, y, u);
    }

    int query(int p, int l, int r, int x)
    {
        if(l == r)
            return tree[p];
        int m = l + r >> 1;
        int ans = tree[p];
        int sub = 0;

        if(x <= m)
            sub = query(p << 1, l, m, x);
        else
            sub = query(p << 1 | 1, m + 1, r, x);
        if(!ans)
            return sub;
        if(!sub)
            return ans;
        
        int flag = cmp(calc(ans, x), calc(sub, x));
        if(flag == -1 || (flag == 0 && sub < ans))
            return sub;
        return ans;
    }

    int query(int x)
    {
        return query(1, 1, n, x);
    }
};
