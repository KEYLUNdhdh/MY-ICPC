#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Manacher
{
    string t;// 预处理后的字符串
    vector<int> p;// p[i] 表示以 t[i] 为中心的回文半径
    int maxlen;// 原字符串中最长回文子串的长度

    Manacher(const string &s)
    {
        int n = s.length();
        // 预分配内存，极致优化常数，防止 1.1*10^7 数据发生 MLE 或 TLE
        t.assign(2 * n + 3, '#');
        t[0] = '^';// 头部加入防越界字符
        for (int i = 0; i < n;i++)
            t[i * 2 + 2] = s[i];

        t[n * 2 + 2] = '$';// 尾部加入防越界字符

        int m = t.length();
        p.assign(m, 0);
        int mid = 0, r = 0;
        maxlen = 0;

        // 马拉车核心逻辑
        for (int i = 1; i < m - 1;i++)
        {
            if(i < r)
                p[i] = min(r - i, p[2 * mid - i]);
            else
                p[i] = 1;
        
            // 中心扩展（因为头部和尾部有 ^ 和 $，所以不需要显式判断越界）
            while(t[i - p[i]] == t[i + p[i]])
                p[i]++;

            // 更新当前能向右延伸的最远回文串的中心和右边界
            if(i + p[i] > r)
            {
                mid = i;
                r = i + p[i];
            }

            // p[i] - 1 恰好等于原字符串中以此为中心的回文串长度
            maxlen = max(maxlen, p[i] - 1);
        }
    }

    // 如果需要获取某点作为中心的最长回文长度，可以额外加这个方法
    // 传入原字符串的下标，返回以该点为中心的最长回文长度（奇数长度）
    int specific(int idx)
    {
        return p[idx * 2 + 2] - 1;
    }
};