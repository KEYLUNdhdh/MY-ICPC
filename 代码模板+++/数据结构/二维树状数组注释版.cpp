#include <bits/stdc++.h>
using namespace std;
//详见typora
template<typename T>
struct FenWick
{
    int n, m;
    // 在每个节点维护 4 个值，用于区间修改区间查询的数学展开
    struct Node
    {
        T d1, d2, d3, d4;
        Node() : d1(0), d2(0), d3(0), d4(0) {}
    };

    vector<Node> tr;// 扁平化一维数组优化常数和缓存命中率
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
    // 将二维坐标映射到一维
    inline int id(int x, int y) const
    {
        return x * (m + 1) + y;
    }
    // 单点差分更新
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
    // 二维区间加法操作 (左上角 x1, y1，右下角 x2, y2)
    void rangeAdd(int x1, int y1, int x2, int y2    , T v)
    {
        add(x1, y1, v);
        add(x2 + 1, y1, -v);
        add(x1, y2 + 1, -v);
        add(x2 + 1, y2 + 1, v);
    }
    // 求左上角 (1, 1) 到右下角 (x, y) 的前缀和
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
    // 求左上角 (x1, y1) 到右下角 (x2, y2) 的子矩阵和
    T rangeSum(int x1, int y1, int x2, int y2)
    {
        return query(x2, y2) - (query(x1 - 1, y2)) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};