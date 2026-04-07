#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<typename T>
struct Fenwick
{
    int n;
    vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n + 1, T{});
    }

    void add(int x,T v)
    {
        for (int i = x; i <= n;i += i & (-i))
        {
            a[i] += v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0;i -= i & (-i))
        {
            ans += a[i];
        }
        return ans;
    }

    T rangeSum(int l,int r)
    {
        return sum(r) - sum(l - 1);
    }
    //select的功能是找到最大的位置 x，使得前缀和到x时 < k
    //核心步骤：起点：从最大的 2 的幂次（比如 2^18）开始尝试。
    //试探：看当前的 x 加上步长 i 后，对应节点 a[x + i] 的值。为什么可以直接加？ 因为在树状数组中，当 i 是 2 的幂次时，a[x + i] 恰好存储了左开右闭区间 (x, x+i] 的和。
    //决策：如果 cur + a[x + i] 还没超过 k，说明目标位置还在更右边。我们把 x 挪过去，并更新当前累计的和 cur。如果超过了 k，说明跳过头了，我们不做操作，减小步长 i 继续试。
    //这本质是对前缀和进行二分查找，所以必须保证前缀和是单调不减的。
    // 也就是说，你的树状数组中所有的 add(x, v) 中的 v 必须 大于0。如果数组里有负数，前缀和就不再单调，二分（倍增）逻辑就会失效。
    int select(const T &k)
    {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i;i >>= 1)
        {
            if(x + i <= n && cur + a[x + i] <= k)
            {
                x += i;
                cur += a[x];
            }
        }
        return x;
    }
};