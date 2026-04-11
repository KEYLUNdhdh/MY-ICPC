#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct FenWick
{
    int n, m;
    struct Node
    {
        T d1, d2, d3, d4;
        Node() : d1(0), d2(0), d3(0), d4(0) {}
    };

    vector<Node> tr;
    FenWick(int n_ = 0, int m_ = 0)
    {
        init(n_, m_);
    }

    void init(int n_ = 0, int m_ = 0)
    {
        n = n_;
        m = m_;
        tr.assign((n + 1) * (m + 1), Node());
    }

    inline int id(int x, int y) const
    {
        return x * (m + 1) + y;
    }

    void add(int x, int y, T v)
    {
        for (int i = x; i <= n;i += i & (-i))
        {
            for (int j = y; j <= m;j += j & (-j))
            {
                int pos = id(i, j);
                tr[pos].d1 += v;
                tr[pos].d2 += v * x;
                tr[pos].d3 += v * y;
                tr[pos].d4 += v * x * y;
            }
        }
    }

    void rangeAdd(int x1, int y1, int x2, int y2    , T v)
    {
        add(x1, y1, v);
        add(x2 + 1, y1, -v);
        add(x1, y2 + 1, -v);
        add(x2 + 1, y2 + 1, v);
    }

    T query(int x, int y)
    {
        T ans{};
        for (int i = x; i > 0; i-= i & (-i))
        {
            for (int j = y; j > 0;j -= j & (-j))
            {
                int pos = id(i, j);
                ans += tr[pos].d1 * (x + 1) * (y + 1) - tr[pos].d2 * (y + 1) - tr[pos].d3 * (x + 1) + tr[pos].d4;
            }
        }
        return ans;
    }

    T rangeSum(int x1, int y1, int x2, int y2)
    {
        return query(x2, y2) - (query(x1 - 1, y2)) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};