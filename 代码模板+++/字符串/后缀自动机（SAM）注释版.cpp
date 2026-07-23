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
    bool isSubstring(const string & query)
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

    // 查询原字符串中不同子串的总数
    i64 distinctSubstringCount() const
    {
        i64 ans = 0;
        // 每个 u 都增加这么多
        for(int u = 2; u <= sz; u++)
            ans += t[u].len - t[t[u].link].len;
        return ans;
    }

    // 查询本质不同子串长度总和
    i64 distinctSubstringLengthSum() const
    {
        i64 ans = 0;

        for(int u = 2; u <= sz; u++)
        {
            i64 l = t[t[u].link].len + 1;
            i64 r = t[u].len;
            ans += (l + r) * (r - l + 1) / 2;
        }

        return ans;
    }

    // 查询与另一个字符串的最长公共子串的长度
    int LCS(const string &s) const
    {
        int p = 1;// 当前匹配字符串在 SAM 中所处的状态，也就是当前位于t[p]
        int len = 0;// 当前实际匹配字符串的实际长度。
        int ans = 0;

        for(char c : s)
        {
            int x = getId(c);

            // 当前字符不能直接接上，我们就往回跳，尝试更短的后缀
            while(p != 1 && !t[p].next[x])
            {
                p = t[p].link;
                len = t[p].len;// 拿到这个endpos等价类里面最长的那个字符串
            }

            // 当前字符可以直接接上
            if(t[p].next[x])
            {
                p = t[p].next[x];// 往下跳
                len++;// 长度加一
            }
            else// 如果我们while循环干到了根节点，说明得从零开始匹配了
            {
                p = 1;
                len = 0;
            }
            //每加入一个字符都得更新下答案。
            ans = max(ans, len);
        }
        return ans;
    }

    // 当前 SAM 应当由 strs 中的一个基准字符串构建。
    // 求该基准字符串与 strs 中所有字符串的最长公共子串。
    // skip 表示跳过 strs[skip]，通常它就是构建 SAM 的最短字符串。
    int multiLCS(const vector<string> &strs) const
    {
        if(strs.empty())
            return 0;

        // rk：所有 SAM 状态按 len 从小到大排序。
        int maxlen = 0;
        for (int i = 1; i <= sz; i++)
            maxlen = max(maxlen, t[i].len);

        vector<int> c(maxlen + 1, 0);
        vector<int> rk(sz + 1, 0);

        for (int i = 1; i <= sz; i++)
            c[t[i].len]++;

        for (int i = 1; i <= maxlen; i++)
            c[i] += c[i - 1];

        for (int i = sz; i >= 1; i--)
            rk[c[t[i].len]--] = i;

        // common[u]：
        // 到目前为止，所有已处理字符串在状态 u 上
        // 共同能够匹配的最大长度。
        // 构建 SAM 的基准字符串对状态 u 天然可以匹配 len[u]。
        vector<int> common(sz + 1);

        for (int i = 1; i <= sz; i++)
            common[i] = t[i].len;

        // best[u]：当前字符串在状态 u 上能够匹配的最大长度。
        vector<int> best(sz + 1);

        for (int id = 0; id < (int)strs.size(); id++)
        {
            const string &s = strs[id];

            fill(best.begin(), best.end(), 0);

            int p = 1;
            int curlen = 0;

            // * 在当前 SAM 上匹配字符串 s。
            for(char ch : s)
            {
                int idx = getId(ch);

                while(p != 1 && !t[p].next[idx])
                {
                    p = t[p].link;
                    curlen = min(curlen, t[p].len);
                }

                if(t[p].next[idx])
                {
                    p = t[p].next[idx];
                    curlen++;
                }
                else
                {
                    p = 1;
                    curlen = 0;
                }

                best[p] = max(best[p], curlen);
            }

            // 按照 len 从大到小，沿 suffix link 传播。
            // 如果状态 u 匹配了 best[u]，
            // 那么 fa = link[u] 至少可以匹配：min(best[u], len[fa])
            for (int i = sz; i >= 2; i--)
            {
                int u = rk[i];
                int fa = t[u].link;

                best[fa] = max(
                    best[fa],
                    min(best[u], t[fa].len)
                );
            }

            // 公共子串要求出现在每个字符串中，
            // 因此对每个状态取最小值。
            for (int i = 2; i <= sz; i++)
                common[i] = min(common[i], best[i]);
        }

        int ans = 0;

        for (int i = 2; i <= sz; i++)
            ans = max(ans, common[i]);

        return ans;
    }
};