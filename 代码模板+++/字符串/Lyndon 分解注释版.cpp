#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

vector<string> duval(const string &s)
{
    int n = s.length();
    int i = 0;
    vector<string> res;

    while(i < n)
    {
        int j = i + 1, k = i;
        // 只要还没越界，并且趋势没有断裂 (s[j] >= s[k])，就一直往后贪心吃字符
        while(j < n && s[j] >= s[k])
        {
            if(s[j] > s[k])
                k = i; // 趋势向上，重置周期
            else
                k++; // 维持周期
            j++;
        }

        // 走到这里，必然是因为 s[j] < s[k] 导致 while 结束
        // 或者是扫到了字符串末尾。此时按周期长度 (j - k) 切割
        while(i <= k)
        {
            res.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return res;
}