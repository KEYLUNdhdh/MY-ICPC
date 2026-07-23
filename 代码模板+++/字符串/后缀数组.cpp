#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SuffixArray
{
    int n;
    vector<int> sa;
    vector<int> rk;
    vector<int> height;

    SuffixArray() = default;

    explicit SuffixArray(const string &str)
    {
        build(str);
    }

    // str 0 - index
    void build(const string &str)
    {
        n = str.size();

        //1 - index
        string s = " " + str;
        sa.assign(n + 1, 0);
        rk.assign(2 * n + 2, 0);

        vector<int> oldrk(2 * n + 2, 0);
        vector<int> id(n + 1, 0);
        vector<int> cnt(max(n, 256) + 1, 0);

        int m = 256;

        for (int i = 1; i <= n;i++)
        {
            rk[i] = static_cast<unsigned char>(s[i]) + 1;
            cnt[rk[i]]++;
        }

        for (int i = 1; i <= m;i++)
            cnt[i] += cnt[i - 1];

        for (int i = n; i >= 1;i--)
            sa[cnt[rk[i]]--] = i;

        for (int w = 1, p = 0;; w <<= 1)
        {
            p = 0;

            for (int i = max(1, n - w + 1); i <= n;i++)
                id[++p] = i;

            for (int i = 1; i <= n;i++)
                if(sa[i] > w)
                    id[++p] = sa[i] - w;

            fill(cnt.begin(), cnt.begin() + m + 1, 0);

            for (int i = 1; i <= n;i++)
                cnt[rk[id[i]]]++;
            for (int i = 1; i <= m;i++)
                cnt[i] += cnt[i - 1];
                
            for (int i = n; i >= 1;i--)
                sa[cnt[rk[id[i]]]--] = id[i];

            oldrk = rk;
            rk[sa[1]] = 1;
            p = 1;

            for (int i = 2; i <= n;i++)
            {
                int x = sa[i - 1];
                int y = sa[i];
                bool same = oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
                rk[y] = same ? p : ++p;
            }

            m = p;
            if(p == n)
                break;
        }
        buildHeight(s);
    }

    void buildHeight(const string &s)
    {
        height.assign(n + 1, 0);
        int k = 0;

        for (int i = 1; i <= n;i++)
        {
            int rki = rk[i];
            if(rki == 1)
            {
                k = 0;
                continue;
            }

            int j = sa[rki - 1];

            while(i + k <= n && j + k <= n && s[i + k] == s[j + k])
                k++;

            height[rki] = k;
            if(k > 0)
                k--;
        }
    }

};