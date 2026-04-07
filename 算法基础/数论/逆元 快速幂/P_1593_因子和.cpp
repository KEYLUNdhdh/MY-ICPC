//约数和公式
//如果一个数 N 的质因数分解为 N = p1^e1 * p2^e2...，那么 N 的所有约数之和实际上就是从每个质因子的幂集合中各选一个相乘再求和。其公式展开形式就是：sigma(N) = (1 + p1 + p1^2 + ... + p1^e1)(1 + p2 + p2^2 + ... + p2^e2)...这本质上和子集乘积和的构造逻辑是一模一样的：利用乘法分配律，让每一个可能的组合（子集）在展开式中出现且仅出现一次。
//其实展开后就是所有因数之后。因为每个多项式内部的选择一个特定的项对应每个质因数的不同选择。即根据多项式的乘法规则，每一个组合都唯一对应了多项式展开式中的一个项，展开后的每一项都是一个因数，他们之和就是我们的目标
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 9901;
int a, b;
int qpow(int a,int b)
{
    int res = 1;
    a = a % MOD;
    // 处理 a 为负数的情况，确保 a 在 [0, MOD-1]
    if(a < 0)
        a += MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}

int inv(int n)
{
    return qpow(n, MOD - 2);
}


signed main()
{
    cin >> a >> b;
    if(a == 0)
    {
        cout << 0;
        return 0;
    }
    int ans = 1;
    for (int i = 2; i * i <= a;i++)
    {
        if(a % i == 0)
        {
            int cnt = 0;
            while(a % i == 0)
            {
                cnt++;
                a /= i;
            }

            int n = cnt * b;
            int p = i % MOD;
            if((p - 1) % MOD == 0)//如果p - 1在模MOD下没有逆元
            {
                //此时p的任意次模MOD后均为一，加起来就是1 + n
                // 等比数列 1 + p + ... + p^n，每一项模 MOD 都是 1
                // 共有 n + 1 项，所以总和为 n + 1
                ans = ans * (1 + n) % MOD;
            }
            else
            {
                // 约数和公式的一项：(p^(n+1) - 1) / (p - 1)
                int z = (qpow(p, n + 1) - 1 + MOD) % MOD;
                int m = inv(p - 1) % MOD;
                ans = ans * z * m % MOD;
            }
        }
    }
    if(a > 1)
    {
        int p = a % MOD;
        int n = b;
        if((p - 1) % MOD == 0)
            ans = ans * (1 + n) % MOD;
        else
        {
            int z = (qpow(p, n + 1) - 1 + MOD) % MOD;
            int m = inv(p - 1) % MOD;
            ans = ans * z * m % MOD;
        }
    }
    cout << ans % MOD;
}