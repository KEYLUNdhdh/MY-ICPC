#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Mo
{
    struct Query
    {
        int l, r, id;
    };

    int n, m, blockSize;
    vector<int> a;
    vector<Query> queries;
    vector<i64> ans;

    // ===== 以下为题目特定状态，换题时根据需要修改 =====
    vector<int> cnt;
    i64 cur_ans;

    Mo (int n_, int m_, const vector<int> &a_, int max_val)
    {
        n = n_;
        m = m_;
        a = a_;
        blockSize = max(1, (int)(n / sqrt(m)));
        ans.assign(m, 0);
        cnt.assign(max_val + 1, 0);
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
        int x = a[idx];
        cur_ans += 2ll * cnt[x] + 1;
        cnt[x]++;
    }

    inline void del(int idx)
    {
        int x = a[idx];
        cur_ans -= 2ll * cnt[x] - 1;
        cnt[x]--;
    }
    // ==================================================

    vector<i64> run()
    {
        sort(queries.begin(), queries.end(), [&](const Query &q1, const Query &q2)
        { 
            int b1 = q1.l / blockSize;
            int b2 = q2.l / blockSize;
            if(b1 != b2)
                return b1 < b2;
            return (b1 & 1) ? q1.r < q2.r : q2.r < q1.r; 
        });

        int L = 1, R = 0;
        for(const auto& q : queries)
        {
            while(L > q.l)
                add(--L);
            while(R < q.r)
                add(++R);
            while(L < q.l)
                del(L++);
            while(R > q.r)
                del(R--);
            ans[q.id] = cur_ans;
        }

        return ans;
    }
};