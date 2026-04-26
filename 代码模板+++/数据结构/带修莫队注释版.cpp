#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct MoUpdate
{
    // 查询结构体增加了一维：时间 t
    struct Query
    {
        int l, r, t, id;
    };
    // 新增：修改操作结构体
    struct Update
    {
        int pos, val;
    };

    int n, blockSize;
    vector<int> a;
    vector<Query> queries;
    vector<Update> updates;
    vector<int> ans;
    // ===== 以下为题目特定状态 =====
    vector<int> cnt;
    int cur_ans;// 本题只要求颜色种类数，用 int 即可
    // n_ 为序列长度，a_ 为原序列（1-indexed），max_val 为颜色的最大值
    MoUpdate(int n_, const vector<int> &a_, int max_val)
    {
        n = n_;
        a = a_;
        // 带修莫队的理论最优分块大小是 n 的 2/3 次方
        blockSize = max(1, (int)pow(n, 2. / 3.));
        cnt.assign(max_val + 1, 0);
        cur_ans = 0;       
        // 塞入一个虚拟的第 0 次修改，让真实的修改操作从下标 1 开始 
        updates.push_back({0, 0});
    }
    // ==================================================
    void addQuery(int l, int r, int t, int id)
    {
        queries.push_back({l, r, t, id});
    }

    void addUpdate(int pos, int val)
    {
        updates.push_back({pos, val});
    }

    // ===== 核心转移逻辑 =====
    // 本题要求统计不同颜色的数量
    inline void add(int idx)
    {
        int x = a[idx];
        if(cnt[x] == 0)
            cur_ans++;// 如果这种颜色之前没有出现过，种类数+1
        cnt[x]++;
    }

    inline void del(int idx)
    {
        int x = a[idx];
        cnt[x]--;
        if(cnt[x] == 0)
            cur_ans--;// 如果这种颜色没了，种类数-1
    }

    // 新增：时间轴移动时的修改应用/撤销逻辑
    inline void applyUpdate(int t, int L, int R)
    {
        int p = updates[t].pos;
        // 如果当前修改的位置恰好在当前莫队维护的区间内，它会影响答案
        if(p >= L && p <= R)
        {
            del(p);// 先把旧颜色删掉
            swap(a[p], updates[t].val);// 核心魔法：交换
            add(p);// 把新颜色加进来
        }
        else
        {
            // 如果不在区间内，不影响当前答案，但序列的状态必须改变（为后续查询做准备），因为我们修改了区间[L, R]之外的值
            swap(a[p], updates[t].val);
        }
    }
    // =========================================

    vector<int> run()
    {
        // 带修莫队的灵魂排序：先按 L 所在块排，再按 R 所在块排，最后按时间 T 排
        sort(queries.begin(), queries.end(), [&](const Query &q1, const Query &q2)
        {
            int b1 = q1.l / blockSize;
            int b2 = q2.l / blockSize;
            if(b1 != b2)
                return b1 < b2;
            int r1 = q1.r / blockSize;
            int r2 = q2.r / blockSize;
            if(r1 != r2)
                return r1 < r2;
            
            // L和R都在同个块内，按时间先后排
            // 这里加入了一个常数优化：奇偶块交替排序（类似普通莫队）
            return (r1 & 1) ? q1.t < q2.t : q1.t > q2.t;
        });

        ans.assign(queries.size(), 0);
        int L = 1, R = 0, T = 0;// T 代表当前执行到了第几次修改操作
        for(const auto &q : queries)
        {
            while(L > q.l)
                add(--L);
            while(R < q.r)
                add(++R);
            while(L < q.l)
                del(L++);
            while(R > q.r)
                del(R--);

            // 时间轴 T 的移动
            while(T < q.t)
                applyUpdate(++T, L, R);// 穿越到未来
            while(T > q.t)
                applyUpdate(T--, L, R);// 倒退回过去

            ans[q.id] = cur_ans;
        }
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 初始化带修莫队，本题颜色值最大为 10^6
    MoUpdate mo(n, a, 1000000);

    int q_id = 0; // 查询的独立编号
    int t_cnt = 0; // 当前经历了多少次修改

    for (int i = 0; i < m; i++)
    {
        char op;
        cin >> op;
        if (op == 'Q')
        {
            int l, r;
            cin >> l >> r;
            // 记录下当前查询是在第 t_cnt 次修改之后进行的
            mo.addQuery(l, r, t_cnt, q_id++);
        }
        else if (op == 'R')
        {
            int pos, val;
            cin >> pos >> val;
            mo.addUpdate(pos, val);
            t_cnt++;
        }
    }

    vector<int> res = mo.run();
    for (int i = 0; i < q_id; i++)
    {
        cout << res[i] << "\n";
    }

    return 0;
}