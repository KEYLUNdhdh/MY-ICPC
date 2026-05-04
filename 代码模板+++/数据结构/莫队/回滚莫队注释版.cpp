#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct RollbackMo
{
    struct Query
    {
        int l, r, id;
    };

    int n, m, blockSize;
    vector<int> a;
    vector<Query> queries;  
    vector<int> ans;// 注意：距离最大是N，所以int就够了

    // ===== 特定状态 (以求区间相同元素最大距离为例) =====
    vector<int> firstpos, lastpos;
    int curans;// 仅由右指针扩展产生的全局最大值

    RollbackMo(int n_, int m_, const vector<int> &a_, int maxval)
    {
        n = n_;
        m = m_;
        a = a_;
        blockSize = max(1, (int)(n / sqrt(m)));// 经典分块大小
        ans.assign(m, 0);

        // 如果 max_val 过大(比如1e9)，需要在外面将 a 数组离散化！
        firstpos.assign(maxval + 1, 0);
        lastpos.assign(maxval + 1, 0);
    }

    // ==================================================
    void addQuery(int l, int r, int id)
    {
        queries.push_back({l, r, id});
    }

    // 处理左右端点在同一个块内的询问 (暴力 O(sqrt(N)))
    //这个视具体情况而定
    int bruteForce(int l, int r)
    {
        int res = 0;
        for (int i = l; i <= r;i++)
        {
            if(!firstpos[a[i]])
                firstpos[a[i]] = i;
            res = max(res, i - firstpos[a[i]]);
        }
        // 擦屁股，恢复白纸状态
        for (int i = l; i <= r;i++)
        {
            firstpos[a[i]] = 0;
        }
        return res;
    }

    //同样，这个run具体情况具体分析
    vector<int> run()
    {
        // 🚨 排序核心：同块内按右端点严格递增！绝不能用奇偶块优化！
        sort(queries.begin(), queries.end(), [&](const Query &q1, const Query &q2)
        {
            int b1 = q1.l / blockSize;
            int b2 = q2.l / blockSize;
            if(b1 != b2)
                return b1 < b2;
            return q1.r < q2.r;
        });

        int lastblock = -1;
        int L = 1, R = 0;

        for(const auto &q : queries)
        {
            int curblock = q.l / blockSize;
            // 1. 跨块了，初始化新块的状态
            if(curblock != lastblock)
            {
                // 把上一个块右指针弄脏的数组擦干净
                for (int i = R; i >= L;i--)
                {
                    firstpos[a[i]] = 0;
                    lastpos[a[i]] = 0;
                }
                // 左指针待命在当前块的右边界外侧一个位置
                L = (curblock + 1) * blockSize;
                R = L - 1;
                curans = 0;
                lastblock = curblock;
            }
            // 2. 同块暴力处理
            if(curblock == q.r / blockSize)
            {
                ans[q.id] = bruteForce(q.l, q.r);//在一个块里面暴力就行
                continue;
            }

            // 1. 右指针：无脑向右（全局状态） R (永久性扩展)，不用回滚。
            while(R < q.r)
            {
                R++;
                if(!firstpos[a[R]])
                    firstpos[a[R]] = R;// 第一次出现
                lastpos[a[R]] = R;// 不断更新最后一次出现
                curans = max(curans, R - firstpos[a[R]]);
            }

            // 2. 左指针：往左试探（临时状态）,需要记录his状态进行回滚。
            int tmpL = L;
            int tmpans = curans;// 继承右指针打下的江山

            while(tmpL > q.l)
            {
                tmpL--;
                int x = a[tmpL];
                //如果右边没出现过这个数，那它在左边第一次被遇到，就是这个数最靠右的位置！
                if(!lastpos[x])
                    lastpos[x] = tmpL;
                tmpans = max(tmpans, lastpos[x] - tmpL);
            }
            
            ans[q.id] = tmpans;

            // 3. 回滚：左指针撤退（抹除痕迹）
            for (int i = q.l; i < L;i++)
            {
                int x = a[i];
                if(lastpos[x] == i)
                    lastpos[x] = 0;
            }
        }

        return ans;
    }
};