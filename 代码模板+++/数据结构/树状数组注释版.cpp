#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<typename T>
struct Fenwick
{
    int n;
    // 核心改造：开两棵树
    // t1 维护 D_i 的前缀和
    // t2 维护 D_i * i 的前缀和
    vector<T> t1, t2;
    
    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        t1.assign(n + 1, T{});
        t2.assign(n + 1, T{});
    }
    // 内部的单点更新操作（供区间加减调用）
    void add(int x,T v)
    {
        T v2 = v * x;// 提取算出 v * x，注意这里是乘原始的 x，不是下面的 i
        for (int i = x; i <= n;i += i & (-i))
        {
            t1[i] += v;
            t2[i] += v2;
        }
    }
    //新增：真正的区间修改，区间 [l, r] 加上 v
    void rangeAdd(int l, int r, T v)
    {
        add(l, v);
        add(r + 1, -v);
    }
    // 内部的前缀和求法（应用裂解公式）
    T sum(int x)
    {
        T sum1{}, sum2{};
        for (int i = x; i > 0;i -= i & (-i))
        {
            sum1 += t1[i];
            sum2 += t2[i];
        }
        // 数学魔法变现： (x + 1) * sum(D_i) - sum(D_i * i)
        return sum1 * (x + 1) - sum2;
    }
    //真正的区间查询，求区间 [l, r] 的和
    T rangeSum(int l,int r)
    {
        return sum(r) - sum(l - 1);
    }
    
};