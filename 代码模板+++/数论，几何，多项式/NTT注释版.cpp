#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const i64 MOD = 998244353;
const int G = 3;// 998244353 的原根

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

namespace NTT
{
    vector<i64> rev;
    void initRev(int limit)
    {
        if(rev.size() == limit)
            return;
        int l = __builtin_ctz(limit);
        rev.resize(limit);
        for (int i = 0; i < limit;i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    }

    // type = 1 为正变换，type = -1 为逆变换
    void transform(vector<i64> &a, int flag)
    {
        int n = a.size();

        initRev(n);
        for(int i = 0;i < n;i++)
            if(i < rev[i])
                swap(a[i], a[rev[i]]);

        for (int mid = 1; mid < n;mid <<= 1)
        {
            i64 wn = qpow(G, (MOD - 1) / (mid << 1));// 根据原根计算当前的单位根
            if(flag == -1)// 逆变换则取逆元
                wn = qpow(wn, MOD - 2);

            for (int i = 0; i < n;i += (mid << 1))
            {
                i64 w = 1;
                for (int j = 0; j < mid;j++, w = w * wn % MOD)
                {
                    i64 x = a[i + j];
                    i64 y = w * a[i + j + mid] % MOD;
                    // 加速取模
                    a[i + j] = (x + y >= MOD ? x + y - MOD : x + y);
                    a[i + j + mid] = (x - y < 0 ? x - y + MOD : x - y);
                }
            }
        }

        // 如果是逆变换，最后需要除以长度 n
        if(flag == -1)
        {
            i64 invN = qpow(n, MOD - 2);
            for (int i = 0; i < n;i++)
                a[i] = a[i] * invN % MOD;
        }
    }
}