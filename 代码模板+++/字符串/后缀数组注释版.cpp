#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SuffixArray
{
    int n;
    // 这 sa, rk 里面存的都是 1 - index
    vector<int> sa;// sa[i]：字典序第 i 小的后缀起点
    vector<int> rk;// rk[i]：从位置 i 开始的后缀的字典序排名
    vector<int> height; // height[i] = LCP(sa[i - 1], sa[i])

    SuffixArray() = default;

    explicit SuffixArray(const string &str)
    {
        build(str);
    }

    // 输入 str 为 0-index
    // 内部统一转换成 1-index
    void build(const string &str)
    {
        n = str.size();

        string s = " " + str;
        sa.assign(n + 1, 0);
        rk.assign(2 * n + 2, 0);

        vector<int> oldrk(2 * n + 2, 0);
        vector<int> id(n + 1, 0);
        vector<int> cnt(max(n, 256) + 1, 0);

        // 初始时按照单个字符排序。
        // 排名 0 留给越界位置，因此字符编码整体加 1。
        int m = 256;

        // 这里使用计数排序，对单个字符进行排序
        for (int i = 1; i <= n;i++)
        {
            rk[i] = static_cast<unsigned char>(s[i]) + 1;
            cnt[rk[i]]++;
        }

        for (int i = 1; i <= m;i++)
            cnt[i] += cnt[i - 1];

        // 倒序放置是为了保证计数排序的稳定性。
        for (int i = n; i >= 1;i--)
            sa[cnt[rk[i]]--] = i;


        // 已知长度为 w 的前缀排名，
        // 求长度为 2w 的前缀排名。
        for (int w = 1, p = 0;; w <<= 1)
        {
            p = 0;

            // 第二关键字为空的后缀：
            // i + w > n
            // 等价于 i > n - w
            // 它们的第二关键字排名为 0，因此最先加入。
            for (int i = max(1, n - w + 1); i <= n;i++)
                id[++p] = i;

            // 如果后缀 sa[i] 按照长度 w 的前缀有序，
            // 那么后缀 sa[i] - w 的第二段恰好从 sa[i] 开始。
            // 因此按照 sa 顺序枚举，可以获得按照第二关键字有序的后缀起点。
            for (int i = 1; i <= n;i++)
                if(sa[i] > w)
                    id[++p] = sa[i] - w;

            // id 已经按照第二关键字有序。
            // 再对第一关键字 rk[id[i]] 做稳定计数排序。
            // 这本质上就是基数排序：
            // 1. 先按第二关键字排序；
            // 2. 再稳定地按第一关键字排序。
            fill(cnt.begin(), cnt.begin() + m + 1, 0);

            for (int i = 1; i <= n;i++)
                cnt[rk[id[i]]]++;
            for (int i = 1; i <= m;i++)
                cnt[i] += cnt[i - 1];
                
            for (int i = n; i >= 1;i--)
                sa[cnt[rk[id[i]]]--] = id[i];

            // 根据二元组(oldrk[i], oldrk[i + w])重新计算排名。
            oldrk = rk; // 保存上一轮排名
            rk[sa[1]] = 1; // 第一个后缀排名为 1
            p = 1;


            for (int i = 2; i <= n;i++)
            {
                // 对于后续相邻后缀，比较二元组：
                int x = sa[i - 1];
                int y = sa[i];
                bool same = oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];// x + w 不怕越界，因为我们开了 2 * n + 2
                rk[y] = same ? p : ++p;// 如果相同则继承，否则开一个新排名.
            }

            m = p;
            // 所有后缀排名互不相同，排序已经完成
            if(p == n)
                break;
        }
        buildHeight(s);
    }

    // s 为已经转换成 1-index 的字符串,这里处理 Height 数组
    void buildHeight(const string &s)
    {
        height.assign(n + 1, 0);
        int k = 0;

        for (int i = 1; i <= n;i++)
        {
            int rki = rk[i];
            // 排名第一的后缀没有前驱
            if(rki == 1)
            {
                k = 0;
                continue;
            }

            int j = sa[rki - 1];

            while(i + k <= n && j + k <= n && s[i + k] == s[j + k])
                k++;

            height[rki] = k;
            // 处理下一个位置 (i+1) 时，不需要从 0 开始比较，至少可以从 (k-1) 开始：
            if(k > 0)
                k--;
        }
    }
};