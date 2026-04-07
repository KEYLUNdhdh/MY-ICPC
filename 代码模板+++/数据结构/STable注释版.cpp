#include <bits/stdc++.h>
using namespace std;
//STable

//1.求区间最大值 (Max)
// vector<int> a = {0, 9, 3, 1, 7, 5}; // 1-index
// 传入 lambda 表达式
// STable st_max(a, [](int x, int y) { return max(x, y); }); 
// cout << st_max.query(2, 4); // 输出 7

// 2. 求区间最小值 (Min)
// STable st_min(a, [](int x, int y) { return min(x, y); }); 

// 3. 求区间最大公约数 (GCD)
// (注意：GCD 也是可重复贡献问题，因为 gcd(x,x)=x)
// std::gcd 包含在 <numeric> 头文件里（bits/stdc++.h 已包含）
// STable st_gcd(a, [](int x, int y) { return std::gcd(x, y); }); 
//4. 求区间按位与 (Bitwise AND)
// STable st_and(a, [](int x, int y) { return x & y; }); 

// 5. 求区间按位或 (Bitwise OR)
// STable st_or(a, [](int x, int y) { return x | y; }); 

// ST 表能够工作的一个绝对前提是，操作必须满足可重复贡献性质（Idempotence）。
// 简单来说，如果一个操作 ⊕ 满足 x⊕x=x，那么它就可以用 ST 表。
// 因为 ST 表在查询时，拼凑出来的两个区间 2^k 是有重叠的（比如查 [1, 6]，是由 [1, 4] 和 [3, 6] 拼成的，中间的 [3, 4] 被计算了两次）。对于加法（x+x=x），重叠会导致结果变大，所以不能用 ST 表；但对于 GCD，中间重叠的部分被求了两次最大公约数，完全不影响最终结果。
//这就是为什么 ST 表经常被称作“可重复贡献问题”的万能解法。
// ST表类似于区间DP，是由两个小区间合并上来的。所以应该先枚举区间长度l（这里即为j），再枚举i.
template<typename T, typename F>
//O(nlogn)
struct STable
{
    int n;
    int maxlog;
    F func;
    // st[i][j] 表示从 i 开始，长度为 2^j 的区间内的最大值
    // 第一维是起点 i，第二维是长度的对数 j
    vector<vector<T>> st;
    //a 1 - index
    STable(const vector<T>& a,const F& f) : func(f)
    {
        n = a.size() - 1;//a[0]废弃了，size - 1
        // __lg(x) 是编译器内置函数，用来求 x 最高位 1 的索引，等价于向下取整的 log2(x)
        maxlog = __lg(n) + 1;
        st.assign(n + 1, vector<T>(maxlog));
        // 初始状态：长度为 2^0 = 1 的区间最大值就是本身
        for (int i = 1; i <= n;i++)
            st[i][0] = a[i];
        for (int j = 1; j < maxlog;j++)
        {
            int len = 1 << (j - 1);//小区间的长度
            for (int i = 1;i <= n - (1 << j) + 1;i++)
                st[i][j] = func(st[i][j - 1], st[i + len][j - 1]);//由i的两个子区间合并上来
        }
    }
    inline T query(int l,int r) const
    {
        if (l > r) 
            swap(l, r);
        int k = __lg(r - l + 1);
        //从l开始，STable最大可覆盖的就是2^j的区间长度，同时将r - (1 << k) + 1作为起始点，长度为2^k的区间刚好覆盖到r.
        return func(st[l][k], st[r - (1 << k) + 1][k]);
    }
};
