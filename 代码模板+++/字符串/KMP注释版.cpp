#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
// 正宗的 KMP 算法封装
//定义一个字符串 s 的 border 为 s 的一个非 s 本身的子串 t，满足 t 既是 s 的前缀，又是 s 的后缀。
struct KMP
{
    vector<int> pi;// pi[i] 记录长度为 i+1 的前缀的最长 border 长度
    // 1. 预处理模式串 p，构造 pi 数组 (也就是 next 数组)
    void build(const string& p)
    {
        int m = p.size();
        pi.assign(m, 0);// pi[0] 显然是 0，因为真子串不能是原串本身
        for (int i = 1, j = 0; i < m;i++)
        {
            // 如果失配，顺着 border 往前跳
            while(j > 0 && p[i] != p[j])
                j = pi[j - 1];
            // 如果匹配上，border 长度加 1
            if(p[i] == p[j])
                j++;
            pi[i] = j;
        }
    }
    // 2. 在文本串 s 中匹配模式串 p
    // 返回所有成功匹配的起始位置 (1-based index)
    vector<int> match(const string& s, const string& p)
    {
        int n = s.size();
        int m = p.size();
        vector<int> res;
        for (int i = 0, j = 0; i < n;i++)
        {
            // 失配时，按 pi 数组跳跃，这是 KMP 的灵魂
            while(j > 0 && s[i] != p[j])
                j = pi[j - 1];
            // 匹配时，同时往后移
            if(s[i] == p[j])
                j++;
            // 模式串完整匹配到了！
            if(j == m)
            {
                // i 是 s 中的末尾匹配下标，起点的 0-based 索引是 i - m + 1
                // 题目要求 1-based，所以要再 + 1，即 i - m + 2
                res.push_back(i - m + 2);
                // 匹配成功后，也要利用 border 跳跃，去寻找下一个可能的重叠匹配
                j = pi[j - 1];
            }
        }
        return res;
    }
};