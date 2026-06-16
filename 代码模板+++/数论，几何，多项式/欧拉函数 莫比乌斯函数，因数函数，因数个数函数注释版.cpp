//欧拉函数，表示小于等于 n 且与 n 互质的正整数个数。
#include <bits/stdc++.h>
using namespace std;

//求解单个函数的欧拉函数。
int phi(int n)
{
    int res = n;
    for (int i = 2; i * i <= n;i++)
    {
        if(n % i == 0)
        {
            while(n % i == 0)
                n /= i;
            res = res / i * (i - 1);
        }
    }
    if(n > 1)
        res = res / n * (n - 1);
    return res;
}

//线性筛同时求欧拉函数和莫比乌斯函数
namespace sieve
{
    int n;
    vector<int> primes;
    vector<int> phi, mu, vis;

    void init(int n_)
    {
        n = n_;
        primes.clear();
        phi.assign(n + 1, 0);
        mu.assign(n + 1, 0);
        vis.assign(n + 1, 0);
    }

    void run()
    {
        phi[1] = 1;
        mu[1] = 1;
        for (int i = 2; i <= n;i++)
        {
            if(!vis[i]) // 没被访问过，说明是质数
            {
                primes.push_back(i);
                phi[i] = i - 1;
                mu[i] = -1;
            }

            for(int p : primes) // 假设已经知道 i，转移到 i * p
            {
                if(1ll * i * p > n)
                    break;

                int x = i * p;
                vis[x] = 1;

                if(i % p == 0)// i本身含有p这个因子
                {
                    phi[x] = phi[i] * p;
                    mu[x] = 0;
                    // 当 p | i 时，说明 p 是当前 i * p 的最小质因子。继续用更大的质数去筛，会破坏“每个合数只被最小质因子筛一次”的性质。
                    break;
                }
                else // p是新加入的这个质数因子
                {
                    phi[x] = phi[i] * (p - 1);//直接乘上phi[p]
                    mu[x] = -mu[i];// 符号翻转
                }
            }
        }
    }
}