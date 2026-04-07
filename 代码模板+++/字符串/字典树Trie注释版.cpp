#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Trie
{
    // ch 存储每个节点的子节点编号，这里包含大小写字母加上数字
    vector<array<int, 70>> ch;
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
};