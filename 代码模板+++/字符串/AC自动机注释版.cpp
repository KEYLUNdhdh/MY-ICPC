#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// ================== 原版字典树板子 ==================
struct Trie
{
    vector<array<int, 70>> ch;
    vector<int> cnt;
    vector<int> pre;

    Trie()
    {
        newNode();
    }

    int newNode()
    {
        ch.push_back({0});
        cnt.push_back(0);
        pre.push_back(0);
        return ch.size() - 1;
    }
    int getId(char c) const
    {
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        return 69;
    }
    void insert(const string& s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u])
                ch[p][u] = newNode();
            p = ch[p][u];
            pre[p]++;
        }
        cnt[p]++;
    }

    int search(const string &s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u])
                return 0;
            p = ch[p][u];
        }
        return cnt[p];
    }

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

    void clear() 
    {
        ch.clear();
        cnt.clear();
        pre.clear();
        newNode();
    }
};

// ================== 这是解耦后的 AC 自动机板子 ==================
// 利用 ": public Trie" 继承你的字典树，免费获得 ch, cnt, insert() 等所有东西
struct ACAuto : public Trie
{
    vector<int> fail;

    ACAuto() : Trie() {}// 构造时自动调用父类 Trie 的构造函数

    // 核心 1：构建 fail 指针与 Trie 图
    void build()
    {
        // 此时所有的 insert 都已经完成，ch.size() 就是节点总数
        int n = ch.size();
        fail.assign(n, 0);// 动态分配 fail 数组的大小

        queue<int> q;
        // 把根节点的第一层子节点放入队列
        for (int i = 0;i < 70;i++)
            if(ch[0][i])
                q.push(ch[0][i]);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            // 遍历字符集，你的字典树数组大小是 70
            for (int i = 0; i < 70;i++)
            {
                if(ch[u][i])
                {
                    // 存在该子节点：它的 fail 指向它父亲的 fail 的对应子节点
                    fail[ch[u][i]] = ch[fail[u]][i];
                    q.push(ch[u][i]);
                }
                // Trie 图优化：如果不存在该子节点，直接让其指向 fail 节点对应的子树
                // 注意这里直接修改了父类的 ch 数组
                else
                    ch[u][i] = ch[fail[u]][i];
            }
        }
    }

    // 核心 2：匹配文本串
    int query(const string &t)
    {
        int u = 0, res = 0;
        for(char c : t)
        {
            u = ch[u][getId(c)];// 直接复用父类的 getId 获取字符映射
            // 顺着 fail 链收集所有匹配到的模式串
            for (int j = u; j && cnt[j] != -1;j = fail[j])
            {
                res += cnt[j];
                cnt[j] = -1;// 剪枝：标记该节点及 fail 链已经统计过，防止重复计算和 TLE
            } 
        }
        return res;
    }

    // 用于处理多测的情况。 
    // 多测时直接开全局变量然后多次清空即可
    void clear()
    {
        Trie::clear();
        fail.clear();
    }
};  

