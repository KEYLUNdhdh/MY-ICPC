#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// 广义后缀自动机利用字典树。
struct Trie
{
    // ch 存储每个节点的子节点编号，这里包含大小写字母加上数字
    vector<array<int, 62>> ch;
    // cnt 记录以当前节点为【结尾】的单词数量
    vector<int> cnt;
    // pre 记录经过当前节点的单词数量（即以此为【前缀】的数量）
    vector<int> pre;
    // 构造函数，初始化根节点
    Trie()
    {
        newNode();// 编号为 0 的节点作为根节点
    }
    // 申请一个新节点
    int newNode()
    {
        ch.push_back({0});// 初始化所有个子节点均为 0
        cnt.push_back(0);
        pre.push_back(0);
        return ch.size() - 1;
    }
    //对每一个字母建立相应的索引映射
    int getId(char c) const
    {
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        assert(false);
        return -1;// 如果是未定义字符，直接报错.

    }
    void insert(const string& s)
    {
        int p = 0;// 从根节点开始
        for(char c : s)
        {
            int u = getId(c);//字符映射
            if(!ch[p][u])
                ch[p][u] = newNode();// 如果没有该子节点，则新建
            p = ch[p][u];
            pre[p]++;//pre 代表 Prefix（前缀）。只要我们路过了这个节点，就给这个节点的 pre 计数器加 1，因为插入的字符串有这个前缀才会经过这里
        }
        cnt[p]++;//在完整走完之后，此时单词已经抵达终点，终点的计数器+1，表明这里是一个完整单词的结尾
    }
    // 查询字符串 s 出现的次数（精确匹配）
    int search(const string &s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u])
                return 0;// 匹配中断，说明不存在
            p = ch[p][u];
        }
        return cnt[p];
    }
    // 查询以字符串 s 为前缀的单词数量
    int searchPrefix(const string &s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u])
                return 0;
            p = ch[p][u];
        }
        return pre[p];
    }

    // 用于处理多测的情况。
    // 多测时直接开全局变量然后多次清空即可
    void clear() 
    {
        ch.clear();
        cnt.clear();
        pre.clear();
        newNode(); // 重新放一个根节点进去
    }
};

// 后缀自动机主体
struct GSAM
{
    static constexpr int SIGMA = 62;

    struct Node 
    {
        int len;
        int link;
        int next[SIGMA];
        i64 siz;
    };

    vector<Node> t;
    // trieState[u] 表示 Trie 节点 u 对应的 SAM 状态
    vector<int> trieState;
    int sz;
    bool built;// 判断GSAM是否已经运行过构建
    bool sizComputed;// 判断是否逆拓扑序统计过子串数量。

    GSAM()
    {
        clear();
    }

    GSAM (const Trie &trie)
    {
        build(trie);
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

    // 相当于初始化
    void clear()
    {
        t.clear();
        t.push_back(Node{});
        t.push_back(Node{});

        sz = 1;
        t[1].len = 0;
        t[1].link = 0;
        trieState.clear();
        built = false;
        sizComputed = false;
    }

    // 分配新节点
    int newNode()
    {
        t.push_back(Node{});
        return ++sz;
    }

    // 从 SAM 状态 last 后面加入字符 idx
    // 返回对应的新状态或已有状态
    int extend(int last, int idx)
    {
        assert(!sizComputed);// 这个要格外注意

        // 广义 SAM 中，该转移可能已经存在
        if(t[last].next[idx])
        {
            int q = t[last].next[idx];

            // q 的长度恰好符合要求，直接复用
            if(t[last].len + 1 == t[q].len)
                return q;

            // 否则拆出一个新的 clone
            int clone = newNode();
            t[clone] = t[q];
            t[clone].len = t[last].len + 1;
            t[clone].siz = 0;

            int p = last;
            while(p > 0 && t[p].next[idx] == q)
            {
                t[p].next[idx] = clone;
                p = t[p].link;
            }

            t[q].link = clone;
            return clone;
        }

        // 转移不存在，基本等同于普通 SAM extend
        int cur = newNode();
        t[cur].len = t[last].len + 1;
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
                int clone = newNode();
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                t[clone].siz = 0;

                while(p > 0 && t[p].next[idx] == q)
                {
                    t[p].next[idx] = clone;
                    p = t[p].link;
                }

                t[q].link = t[cur].link = clone;
            }
        }
        return cur;
    }

    // 如果只需要一条，那就插入一条字符串
    void build(const string &s)
    {
        clear();

        t.reserve(2 * s.size() + 2);

        int last = 1;
        for(char ch : s)
            last = extend(last, getId(ch));

        built = true;
    }

    // 从外部 Trie 上 BFS 建立广义 SAM
    // 传入的是已经插入好所有字符串的字典树
    void build(const Trie &trie)
    {
        clear();

        // Trie 一条边至多产生两个 SAM 状态
        t.reserve(2 * trie.ch.size() + 2);

        trieState.assign(trie.ch.size(), 0);
        trieState[0] = 1;

        queue<int> q;
        q.push(0);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int idx = 0; idx < SIGMA;idx++)
            {
                int v = trie.ch[u][idx];
                if(!v)
                    continue;

                trieState[v] = extend(trieState[u], idx);
                q.push(v);
            }
        }

        // 每个 Trie 节点表示一个不同的字符串前缀。
        // trie.pre[u] 表示有多少个原字符串经过该前缀节点，
        // 即这个前缀作为“结束位置”出现了多少次。
        for (int u = 1; u < (int)trie.ch.size();u++)
        {
            int p = trieState[u];
            t[p].siz += trie.pre[u];
        }

        built = true;
    }

    // 查找是否作为子串出现过
    bool isSubString(const string &query)
    {
        if(query.empty())
            return 0;

        assert(built);
        int p = 1;
        for(char c : query)
        {
            int idx = getId(c);
            if(!t[p].next[idx])
                return false;

            p = t[p].next[idx];
        }
        return true;
    }

    void comSiz()
    {
        assert(built);

        if(sizComputed)
            return;

        int maxlen = 0;
        for (int i = 1; i <= sz;i++)
            maxlen = max(maxlen, t[i].len);

        vector<int> c(maxlen + 1, 0);
        vector<int> rk(sz + 1, 0);

        for (int i = 1; i <= sz;i++)
            c[t[i].len]++;
        for (int i = 1; i <= maxlen;i++)
            c[i] += c[i - 1];
        // rk 按 len 从小到大排列
        for (int i = sz; i >= 1;i--)
            rk[c[t[i].len]--] = i;

        // 按 len 从大到小向 suffix link 传播
        for (int i = sz; i >= 2;i--)
        {
            int u = rk[i];
            t[t[u].link].siz += t[u].siz;
        }
        sizComputed = true;
    }

    // 查询 query 在所有插入字符串中的总出现次数
    // 也就是对于每个字符串，query作为子串到底出现了几次
    i64 count(const string &query)
    {
        if(query.empty())
            return 0;
        comSiz();
        int p = 1;
        for(char c : query)
        {
            int idx = getId(c);
            if(!t[p].next[idx])
                return 0;
            p = t[p].next[idx];
        }
        return t[p].siz;
    }

    // 查询所有原字符串中本质不同子串的总数
    i64 distinctSubStringCount()
    {
        assert(built);
        i64 ans = 0;
        for (int i = 2; i <= sz;i++)
            ans += t[i].len - t[t[i].link].len;
        return ans;
    }

    // 新串与任意一个已插入字符串的最长公共子串长度。
    int LCS(const string &s)
    {
        assert(built);

        int p = 1;
        int len = 0;
        int ans = 0;

        for(char c : s)
        {
            int idx = getId(c);

            while(p != 1 && !t[p].next[idx])
            {
                p = t[p].link;
                len = t[p].len;
            }

            if(t[p].next[idx])
            {
                p = t[p].next[idx];
                len++;
            }
            else
            {
                p = 1;
                len = 0;
            }

            ans = max(ans, len);
        }

        return ans;
    }

    // 在当前 SAM 的候选子串集合中，
    // 求 strs 中所有字符串的最长公共子串。
    // 实战中通常对 strs 中的最短字符串建立 SAM。
    int multiLCS(const vector<string> &strs) const
    {
        assert(built);
        if(strs.empty())
            return 0;

        // order 按照状态 len 从小到大排列。
        // 后面需要逆序传播 best。
        int maxlen = 0;
        for (int i = 1; i <= sz;i++)
            maxlen = max(maxlen, t[i].len);

        // 做计数排序
        vector<int> c(maxlen + 1, 0);
        // 存储 len 从小到大的排序
        vector<int> rk(sz + 1, 0);

        for (int i = 1; i <= sz;i++)
            c[t[i].len]++;
        for (int i = 1; i <= maxlen;i++)
            c[i] += c[i - 1];
        for (int i = sz; i >= 1;i--)
            rk[c[t[i].len]--] = i;

        
        // common[u]:到目前为止，所有已经处理的字符串在状态 u 上能够共同匹配的最大长度。
        // 一开始还没有处理字符串，因此上界为 len[u]。
        vector<int> common(sz + 1, 0);
        for (int i = 1; i <= sz;i++)
            common[i] = t[i].len;

        // 在处理字符串 s 时，best[u] 表示字符串 s 在 u 节点上面成功匹配了最多多长的子串
        vector<int> best(sz + 1, 0);
        for(const string &s : strs)
        {
            // 每处理一个新的 s 都要清空初始化
            fill(best.begin(), best.end(), 0);
            int p = 1;
            int curlen = 0;

            for (char c : s)
            {
                int idx = getId(c);
                // 当前状态无法接上字符时，不断跳 suffix link。
                // 尝试更短的后缀
                while(p != 1 && !t[p].next[idx])
                {
                    p = t[p].link;
                    curlen = min(curlen, t[p].len);
                }

                // 可以往下走就走
                if(t[p].next[idx])
                {
                    p = t[p].next[idx];
                    curlen++;
                }
                else// while 循环跳到起点了，重新开始匹配
                {
                    p = 1;
                    curlen = 0;
                }
                best[p] = max(best[p], curlen);
            }

            // 把信息沿 suffix link 向上传递。
            for (int i = sz; i >= 2;i--)
            {
                int u = rk[i];
                int fa = t[u].link;

                best[fa] = max(best[fa], min(best[u], t[fa].len));
            }

            // 每个单独的状态对所有字符串取最小值
            for (int i = 2; i <= sz;i++)
                common[i] = min(common[i], best[i]);
        }
        int ans = 0;
        // 对所有状态取最大值
        for (int i = 2; i <= sz;i++)
            ans = max(ans, common[i]);

        return ans;
    }
};


// void solve()
// {
//     int n;
//     cin >> n;

//     Trie trie;

//     for (int i = 1; i <= n;i++)
//     {
//         string s;
//         cin >> s;
//         trie.insert(s);
//     }

//     GSAM sam;
//     sam.build(trie);

//     int q;
//     cin >> q;

//     while(q--)
//     {
//         string s;
//         cin >> s;

//         cout << sam.isSubstring(s) << " "
//              << sam.count(s) << "\n";
//     }
// }