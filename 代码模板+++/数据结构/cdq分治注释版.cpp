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
    int cnt;// 有多少个完全一样的元素
    int ans;// 满足偏序的个数

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
        cdq(l, m);// 处理左半边内部
        cdq(m + 1, r);// 处理右半边内部

        // 准备计算【左半边】对【右半边】的贡献
        //因为这层是在大区间内部，所以左半边的所有元素的 A 都小于等于右半边的 A。A 的限制已经被我们踩在脚下了！
        // 按第二维 b 排序，若 b 相同按 c 排序
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
            // 左半边找 b <= 右半边 b 的加入树状数组
            while(i <= m && p[i].b <= p[j].b)
            {
                bit.add(p[i].c, p[i].cnt);
                i++;
            }

            p[j].ans += bit.query(p[j].c);
            j++;
        }
        // 🚨 极其关键：必须手动撤销树状数组，绝对不能 memset，否则退化 O(NK) 必 TLE
        for (int pt = l; pt < i;pt++)
            bit.add(p[pt].c, -p[pt].cnt);
    }

    vector<i64> run()
    {
        // 1. 按第一维 a 排序
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
        // 2. 将完全相同的元素去重压缩
        vector<Element> uniq;
        for (int i = 0; i < p.size(); i++)
        {
            if(i > 0 && p[i] == p[i - 1])
                uniq.back().cnt++;
            else
                uniq.push_back(p[i]);
        }
        p = uniq;
        // 3. 初始答案赋值（相同元素内部已经互相贡献了 cnt - 1 次）
        for(auto &e : p)
            e.ans = e.cnt - 1;//内部就有 `cnt - 1` 个点互相满足条件
        // 4. 跑 CDQ
        if(!p.empty())
            cdq(0, p.size() - 1);
        // 5. 组装最终答案
        vector<i64> res(n, 0);
        for(const auto &e : p)
            res[e.ans] += e.cnt;// 注意要加上 cnt，因为这代表了 cnt 个完全一样的人
        return res;
    }
};