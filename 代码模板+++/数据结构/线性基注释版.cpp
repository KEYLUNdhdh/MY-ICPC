//线性基就是 S 的一个子集 B ,满足：
//1.B 中的数线性无关（即任何非空子集的异或和不为 0）；
//2.S 中的每个数都可以由 B 中某些数的异或和唯一表示。

//线性基的基本性质
// 线性无关：基中任意多个数的异或和不为 0。
// 极小性：去掉任何一个基向量，剩下的数就无法表示所有原集合的异或和。
// 维数：基的大小等于异或空间的维数，且不超过最大数的二进制位数（如 32 位整数不超过 32）。
// 表示唯一性：每个能表示的数，其表示方式（基的选取）是唯一的。
// 封闭性：基的异或组合恰好就是原集合的所有异或和。
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}

//i64
struct Basis
{
    vector<i64> a;// 基向量，a[i] 的最高位为 i
    vector<i64> t;// 时间戳，-1 表示空位
    //插入时：记录每个基向量是何时（或在什么优先级下）被插入的。当新插入的数与已有基向量冲突时，通过比较时间戳大小，决定谁留在高位，谁继续向下尝试，最终每个位置上保留的是该位时间戳最大（即“最新”或“优先级最高”）的向量。

    //查询时：可以指定一个时间阈值 y，只考虑那些时间戳 ≥ y 的基向量参与异或消元。如果最终能把待查询的数 x 消为 0，则说明 x 可以由这些“较新”的基向量线性表示。
    //初始化
    bool zero = false;
    Basis()
    {
        a.resize(64, 0);
        t.resize(64, -1);//t[i] 的默认值 -1 表示该位尚未被占用
    }
    // 插入数 x，时间戳为 y（默认 2e18 表示无穷大）
    //add 函数实现了带时间戳的线性基插入，核心思想是从高位到低位处理，保证每个基向量的最高位唯一，并且每个位上保留的是时间戳最大的向量
    //本质是高斯消元法
    void add(i64 x, i64 y = 2e18)
    {
        for (int i = 63; i >= 0;i--)
        {
            if((x >> i) & 1)
            {
                if (y > t[i])
                {
                    swap(a[i], x);
                    swap(t[i], y);
                }
                x ^= a[i];
            }
        }
        if(x == 0)
            zero = true;
    }
    // 查询 x 能否由时间戳 ≥ y 的基向量表示
    //默认 y = 0 表示考虑所有已插入的基向量
    //对于y = -1的空的就不会考虑了
    bool query(i64 x, i64 y = 0)
    {
        for (int i = 63; i >= 0;i--)
        {
            if(((x >> i) & 1) && t[i] >= y)
                x ^= a[i];
        }
        return x == 0;
    }
    //从高到低贪心尝试
    // 求最大异或和
    i64 getMax() {
        i64 res = 0;
        for (int i = 63; i >= 0; --i) {
            if ((res ^ a[i]) > res)  // 异或后变大则采用
                res ^= a[i];
        }
        return res;
    }
    //所有可能的异或和由这些基向量的任意子集异或得到。所以我们从下往上找，对于从下往上找到的第一个存在的基，我们只用选取它就行。否则，一定给有更高位的1出现
    i64 getMin()
    {
        if(zero)
            return 0;
        for (int i = 0; i <= 63;i++)
        {
            if(a[i])
                return a[i];
        }
        return 0;
    }
    //为了求第 k 小，我们需要将线性基化为“最简形式”，使得每个基向量只有最高位为 1（即形如 2^i），这样所有异或和就对应这些 2^i 的子集异或，并且按大小排序与二进制位直接对应。ps:有点线性代数那味了
    i64 getkth(i64 k)
    {
        if(zero)
        {
            //有0的情况下，如果k为1，直接输出0
            if(k == 1)
                return 0;
            k--;//否则，将 k 减 1，后续只考虑非零的异或和，即第 2 小对应原来的第 1 个非零数，以此类推。
        }
        vector<i64> b = a;//复制，防止修改原数组
        vector<i64> tmp;
        for (int i = 0; i <= 63;i++)
        {
            for (int j = i - 1; j >= 0;j--)
            {
                //消元过程
                if((b[i] >> j) & 1)
                    b[i] ^= b[j];
                
            }
            if(b[i])//如果不为0
                tmp.push_back(b[i]);//tmp 中的元素按最高位从小到大排列（因为 i 从小到大），且每个元素都是 2 的幂。
        }
        i64 cnt = tmp.size();
        if(k >= (1ll << cnt))//可表示的非零异或和共有 2^cnt 个如果 k 大于等于 2^cnt，说明第 k 小不存在，返回 -1。
            return -1;
        i64 res = 0;
        //将 k 视为二进制数，其第 i 位（从 0 开始）为 1 表示选取 tmp[i]（即 2^{对应位权}）。由于 tmp 中元素按位权从小到大排列，这样组合得到的数恰好是第 k 小的非零异或和。
        // 这是因为所有可能的异或和就是这些 2 的幂的子集和，而每个子集对应一个二进制数，且大小顺序与二进制数的大小顺序一致（因为位权越大，数值越大）。
        //用二进制加法模拟一下很快就能发现.
        for (int i = 0; i < cnt;i++)
        {
            if((k >> i) & 1)
                res ^= tmp[i];
        }
        return res;
    }
};

//int 
struct Basis
{
    vector<int> a;
    vector<int> t;
    bool zero = false;

    Basis()
    {
        a.resize(32, 0);
        t.resize(32, -1);
    }

    void add(int x, int y = 1e9)
    {
        for (int i = 31; i >= 0;i--)
        {
            if((x >> i) & 1)
            {
                if (y > t[i])
                {
                    swap(a[i], x);
                    swap(t[i], y);
                }
                x ^= a[i];
            }
        }
        if(x == 0)
            zero = true;
    }

    bool query(int x, int y = 0)
    {
        for (int i = 31; i >= 0;i--)
        {
            if(((x >> i) & 1) && t[i] >= y)
                x ^= a[i];
        }
        return x == 0;
    }

    //从高到低贪心尝试
    int getMax() 
    {
        int res = 0;
        for (int i = 31; i >= 0; i--) 
        {
            chmax(res, res ^ a[i]);
        }
        return res;
    }
    int getMin()
    {
        if(zero)
            return 0;
        for (int i = 0; i <= 31;i++)
        {
            if(a[i])
                return a[i];
        }
        return 0;
    }

    int getkth(int k)
    {
        if(zero)
        {
            if(k == 1)
                return 0;
            k--;
        }
        vector<int> b = a;
        vector<int> tmp;
        for (int i = 0; i <= 31;i++)
        {
            for (int j = i - 1; j >= 0;j--)
            {
                if((b[i] >> j) & 1)
                    b[i] ^= b[j];
                
            }
            if(b[i])
                tmp.push_back(b[i]);
        }
        int cnt = tmp.size();
        if(k >= (1 << cnt))
            return -1;
        int res = 0;
        for (int i = 0; i < cnt;i++)
        {
            if((k >> i) & 1)
                res ^= tmp[i];
        }
        return res;
    }
};