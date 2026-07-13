#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SAM
{
    static constexpr int SIGMA = 70; // depends on the problem

    struct Node
    {
        int len;// 状态表示的最长子串长度
        int link;// Suffix Link (Parent 树指针)
        int next[SIGMA];// 转移边

        // 因为这个节点代表的所有字串endpos一致，所以出现次数应该也相同
        i64 siz;// endpos 集合大小（即子串出现次数）
    };

    vector<Node> t;
    int sz;// 自动机节点总数
    int last;// 插入上一个字符后的状态
    bool sizComputed;
    // 构造函数：预分配内存，SAM 的节点数最多为 2 * n - 1
    SAM(int n)
    {
        t.resize(2 * n + 2);
        sz = 1;// 1 号点是根节点 (初始状态)
        last = 1;
        t[1].len = 0;
        t[1].link = 0;
        sizComputed = 0;
    }

    int getId(char c) const
    {
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        assert(false);
        return -1;
    }

    // 插入字符并维护 SAM 的性质
    void extend(char c)
    {
        assert(!sizComputed);// 第一次统计出现次数后禁止继续扩展

        int idx = getId(c);
        int cur = ++sz;
        t[cur].len = t[last].len + 1;
        t[cur].siz = 1;// 实点，代表原串的一个前缀，出现次数初始为 1

        int p = last;
        while(p > 0 && !t[p].next[idx])
        {
            t[p].next[idx] = cur;
            p = t[p].link;
        }

        if(p == 0)
            t[cur].link = 1;
        else
        {
            int q = t[p].next[idx];
            if(t[p].len + 1 == t[q].len)
                t[cur].link = q;
            else
            {
                int clone = ++sz;
                t[clone].len = t[p].len + 1;
                t[clone].link = t[q].link;

                // 复制转移边
                copy(begin(t[q].next), end(t[q].next), begin(t[clone].next));
                t[clone].siz = 0;// 虚点（被分裂出来的点），初始时不包含当前前缀，siz 为 0

                while(p > 0 && t[p].next[idx] == q)
                {
                    t[p].next[idx] = clone;
                    p = t[p].link;
                }

                t[q].link = t[cur].link = clone;
            }
        }

        last = cur;
    }

    ///
    //  1. 判断子串是否存在（不需要 siz，直接跑）
    bool isSubstirng(const string & query)
    {
        int p = 1;// 从根节点（空串）开始走
        for (char c : query)
        {
            int idx = getId(c);
            if(!t[p].next[idx])
                return false;// 如果顺着明线找不到下一个字符，说明失配了
            p = t[p].next[idx];// 顺着路继续往下走
        }
        return true;// 顺利走完整个 query，说明它是子串！
    }

    // 🌟 新增：内部专用的拓扑序累加函数
    void comSiz()
    {
        if(sizComputed)// 如果已经算过了，直接 return，防止重复累加和 TLE
            return;

        vector<int> c(sz + 1, 0);// 桶，记录每种长度出现的次数
        vector<int> rk(sz + 1, 0);// 排名数组，rk[i] 表示按长度从小到大排名为 i 的节点编号
        // 1. 统计各个 len 的数量
        for (int i = 1; i <= sz;i++)
            c[t[i].len]++;
        // 2. 求前缀和，算出每种 len 在 rk 数组中占据的最高排名位置
        // 有点计数排序的感觉
        for (int i = 1; i <= sz;i++)
            c[i] += c[i - 1];
        // 3. 把每个节点放到它对应的排名位置上
        for (int i = 1; i <= sz;i++)
            rk[c[t[i].len]--] = i;

        // 拓扑序逆序累加   
        // 为什么是拓扑序？因为包含 len 更大的节点一般在图的最底部，也就是出度为 0，所以为逆序拓扑序
        for (int i = sz; i >= 2;i--)
        {
            int u = rk[i];// 按 len 从大到小取出节点编号
            t[t[u].link].siz += t[u].siz;// 把自己的出现次数，上供给自己的干爹 (link)
        }

        sizComputed = 1;// 标记为已完成
    }

    // 2. 查询子串出现次数（全自动档）
    i64 count(const string &query)
    {
        if(query.empty())
            return 0;
            
        comSiz();// 🌟 查询前自动拦截，如果没算过就帮你算，算过就瞬间放行

        int p = 1;
        for(char c : query)
        {
            int idx = getId(c);
            if(!t[p].next[idx])
                return 0;
            p = t[p].next[idx];
        }

        return t[p].siz;// 此时返回的绝对是真实准确的出现次数！
    }
};