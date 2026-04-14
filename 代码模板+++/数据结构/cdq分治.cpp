#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Fenwick
{
    int n;
    vector<i64> tr;
    Fenwick(int n_) : n(n_), tr(n + 1, 0) {}
    void add(int x, int v)
    {
        for (; x <= n; x += x & (-x))
            tr[x] += v;
    }
    i64 query(int x)
    {
        i64 res = 0;
        for (; x > 0; x -= x & (-x))
            res += tr[x];
        return res;
    }
};

struct Element
{
    int a, b, c;
    int cnt;
    int ans;

    bool operator==(const Element &o) const
    {
        return a == o.a && b == o.b && c == o.c;
    }
};

struct CDQ
{
    int n, k;
    vector<Element> p;
    Fenwick bit;

    CDQ(int n_, int k_) : n(n_), k(k_), bit(k_) {}

    void addElement(int a, int b, int c)
    {
        p.push_back({a, b, c, 1, 0});
    }

    void cdq(int l, int r)
    {
        if (l >= r)    
            return;
        int m = l + r >> 1;
        cdq(l, m);
        cdq(m + 1, r);
        auto cmpb = [](const Element &x, const Element &y) -> bool
        {
            if(x.b != y.b)
                return x.b < y.b;
            else
                return x.c < y.c;
        };
        sort(p.begin() + l, p.begin() + m + 1, cmpb);
        sort(p.begin() + m + 1, p.begin() + r + 1, cmpb);

        int i = l, j = m + 1;

        while(j <= r)
        {
            while(i <= m && p[i].b <= p[j].b)
            {
                bit.add(p[i].c, p[i].cnt);
                i++;
            }

            p[j].ans += bit.query(p[j].c);
            j++;
        }

        for (int pt = l; pt < i;pt++)
            bit.add(p[pt].c, -p[pt].cnt);
    }

    vector<i64> run()
    {
        auto cmpa = [](const Element &x, const Element &y) -> bool
        {
            if(x.a != y.a)
                return x.a < y.a;
            else if(x.b != y.b)
                return x.b < y.b;
            else
                return x.c < y.c;
        };
        sort(p.begin(), p.end(), cmpa);

        vector<Element> uniq;
        for (int i = 0; i < p.size(); i++)
        {
            if(i > 0 && p[i] == p[i - 1])
                uniq.back().cnt++;
            else
                uniq.push_back(p[i]);
        }
        p = uniq;

        for(auto &e : p)
            e.ans = e.cnt - 1;

        if(!p.empty())
            cdq(0, p.size() - 1);

        vector<i64> res(n, 0);
        for(const auto &e : p)
            res[e.ans] += e.cnt;
        return res;
    }
};