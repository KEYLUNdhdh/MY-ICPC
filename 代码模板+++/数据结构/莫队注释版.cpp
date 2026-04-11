#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Mo
{
    struct Query
    {
        int l, r, id;// 记录区间的左右端点，以及这是第几个查询（为了最后按顺序输出）
    };
    int n, m, blockSize;
    vector<int> a;// 原数组
    vector<Query> queries;// 存放所有查询
    vector<i64> ans;// 存放所有查询的答案

    // ===== 以下为题目特定状态，换题时根据需要修改 =====
    //这个题目介绍详见typora
    vector<int> cnt;// cnt[x] 记录数字 x 在当前双指针区间内出现了几次
    i64 cur_ans;// 记录当前双指针区间内的总答案（频率平方和）

    Mo (int n_, int m_, const vector<int> &a_, int max_val)
    {
        n = n_;
        m = m_;
        a = a_;
        blockSize = max(1, (int)(n / sqrt(m)));// 核心：分块大小设为 N / sqrt(M)，这是数学证明出的理论最优块长
        ans.assign(m, 0);
        cnt.assign(max_val + 1, 0);// 频次数组的大小取决于数字的最大值
        cur_ans = 0;
    }
    // ==================================================
    void addQuery(int l, int r, int id)
    {
        queries.push_back({l, r, id});
    }
    // ===== 核心转移逻辑：换题时只需修改这两个函数 =====
    inline void add(int idx)
    {
        int x = a[idx]; // 获取当前新进来的数字 x
        cur_ans += 2ll * cnt[x] + 1;// 套用我们的数学公式：答案增加 2c + 1
        cnt[x]++;// 数字 x 的出现频次加 1
    }

    inline void del(int idx)
    {
        int x = a[idx];// 获取当前要被移出去的数字 x
        cur_ans -= 2ll * cnt[x] - 1;// 套用我们的数学公式：答案减少 2c - 1
        cnt[x]--;// 数字 x 的出现频次减 1
    }
    // ==================================================

    vector<i64> run()
    {
        sort(queries.begin(), queries.end(), [&](const Query &q1, const Query &q2)
        { 
            int b1 = q1.l / blockSize;// 计算查询 1 的左端点在第几个块
            int b2 = q2.l / blockSize;// 计算查询 2 的左端点在第几个块
            if(b1 != b2)// 如果左端点不在同一个块，块号小的排前面
                return b1 < b2;
            // 奇偶块优化：左端点同在奇数块，R 升序；同在偶数块，R 降序
            return (b1 & 1) ? q1.r < q2.r : q2.r < q1.r; 
        });
        // 初始状态，构造一个空区间 [1, 0]
        int L = 1, R = 0;
        for(const auto& q : queries)
        {
            // 务必牢记：先扩大区间，后缩小区间！
            while(L > q.l)// 左指针往左扩：加入新元素
                add(--L);
            while(R < q.r)// 右指针往右扩：加入新元素
                add(++R);
            while(L < q.l)// 左指针往右缩：踢出老元素
                del(L++);
            while(R > q.r)// 右指针往左缩：踢出老元素
                del(R--);
            ans[q.id] = cur_ans;// 游标移动到位，保存当前查询的答案
        }

        return ans;
    }
};