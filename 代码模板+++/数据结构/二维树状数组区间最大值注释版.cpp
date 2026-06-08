#include <bits/stdc++.h>
using namespace std;

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

//树状数组不能由0下标，因为 0 & (-0) = 0,死循环
template<typename T>
struct FenwickMax 
{
    int n, m;
    vector<T> tr; // 不再需要维护 Node，只需要一个值即可

    FenwickMax(int n_ = 0, int m_ = 0) 
    {
        init(n_, m_);
    }

    void init(int n_ = 0, int m_ = 0) 
    {
        n = n_;
        m = m_;
        // 初始化为 0。如果是求可能有负数的最大值，这里需要 assign 极小值
        tr.assign((n + 1) * (m + 1), 0); 
    }

    inline int id(int x, int y) const 
    {
        return x * (m + 1) + y;
    }

    // 单点更新，维护前缀最大值
    void update(int x, int y, T v) 
    {
        for (int i = x; i <= n; i += i & (-i)) 
        {
            for (int j = y; j <= m; j += j & (-j)) 
            {
                int pos = id(i, j);
                // 这里用到你个人模板里的 chmax
                chmax(tr[pos], v);
            }
        }
    }

    // 查询前缀最大值 (1, 1) 到 (x, y)
    T query(int x, int y) 
    {
        T ans{}; // 默认为 0
        for (int i = x; i > 0; i -= i & (-i)) 
        {
            for (int j = y; j > 0; j -= j & (-j)) 
            {
                int pos = id(i, j);
                chmax(ans, tr[pos]);
            }
        }
        return ans;
    }
};