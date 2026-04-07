//欧拉函数（Euler's totient function）以及大区间筛法。
//题目定义 qiandao(i) 为 1 ~ i 中与 i 不互质的数的个数。我们知道，欧拉函数 phi(i) 表示的是 1 ~ i 中与 i 互质的数的个数。所以，总数 i 减去互质的个数，就是不互质的个数.
//即qiandao(i) = i -  phi(i)
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 666623333;
const int MAXN = 1e6 + 5;

int l, r;
//这里构建了一个映射，让phi[i] 代表l + i这个数对应的欧拉函数
int phi[MAXN];//存储每个点的欧拉函数的值//初始值为 i，准备用来根据公式连乘(p - 1) / p。
int temp[MAXN];//初始值为 i，用来不断除以已经发现的质因子，最后剩下的部分就是大于 10^6 的质因子。
int isPrime[MAXN];
vector<int> primes;
// 1. 线性筛：预处理出 sqrt(r) 以内的质数
void gp(int n)
{
    fill(isPrime + 2, isPrime + n + 1, 1);
    for (int i = 2; i <= n;i++)
    {
        if(isPrime[i])
            primes.push_back(i);
        for (auto p : primes)
        {
            if(i * p > n)
                break;
            isPrime[i * p] = 0;
            if(i % p == 0)
                break;
        }
    }
}

void solve()
{
    cin >> l >> r;
    gp(1000000);// sqrt(10^12) = 10^6   
    int len = r - l;
    // 2. 初始化区间映射数组
    for (int i = 0; i <= len;i++)
    {
        phi[i] = l + i;// 初始 phi[n] = n
        temp[i] = l + i;// 用于不断除以质因子
    }
    // 3. 利用小质数筛区间
    for(int p : primes)
    {
        // 找到区间内第一个 p 的倍数
        int start = (l + p - 1) / p * p;
        for (int j = start; j <= r;j += p)
        {
            int idx = j - l;
            // 应用 phi(n) = n * (p-1)/p
            phi[idx] = phi[idx] / p * (p - 1);
            // 除掉所有的因子 p
            while(temp[idx] % p == 0)
                temp[idx] /= p;
        }
    }
    int ans = 0;
    // 4. 处理最后可能剩下的大于 10^6 的质因子
    for (int i = 0; i <= len;i++)
    {
        //在遍历完所有小于 10^6 的素数后，如果 val[i] 还不等于 1，说明 i 还有一个大于 10^6 的质因子（且这种质因子最多只有一个，因为两个相乘就超过 10^{12} 了）。此时再对 phi[i] 执行一次公式计算。
        if(temp[i] > 1)
        {
            phi[i] = phi[i] / temp[i] * (temp[i] - 1);
        }
        // qiandao(x) = x - phi(x)
        int val = (l + i - phi[i]) % MOD;
        ans = (ans + val) % MOD;
    }
    cout << ans;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
}