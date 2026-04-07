#include <bits/stdc++.h>
using namespace std;
//1
//exgcd求法
template<class T>
T exgcd(T a,T b,T &x,T &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    T d = exgcd(b, a % b, y, x);

    y = y - (a / b) * x;
    return d;
}
//求a在模m下的逆元
template<class T> 
T inv1(T a,T m)
{
    T x, y;
    T g = exgcd(a, m, x, y);

    if(g != 1)
        return -1;
    return (x % m + m) % m;
} 


//2
//快速幂，仅限模数为质数

template<class T>
T qpow(T a,T b,T MOD)
{
    T res = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}

template <class T>
T inv2(T a,T p)
{
    return qpow(a, p - 2, p);
}

//3
//线性求逆元

vector<int> inv;
void invarr(int n,int p)
{
    inv.assign(n + 5, 0);
    inv[1] = 1;
    for (int i = 2; i <= n;i++)
        inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    return;
}

// int main()
// {
//     invarr(1000, 2);

// }