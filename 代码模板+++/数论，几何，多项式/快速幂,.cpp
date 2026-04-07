#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

//一般快速幂乘法
template<class T>
constexpr T qpow(T a, T b) {
    T res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

//快速幂取模运算
template<class T>
constexpr T qpow(T a,T b,T MOD)
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
// 针对超大整数的乘法取模（防止 a*b 溢出 long long）
// 使用 long double 辅助计算
//根据数学恒等式 a*b = k*p + r（r = (a*b) % p，0 ≤ r < p），则 k = floor(a*b / p)，因此 r = a*b - k*p。
constexpr i64 mod(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p; 
    res %= p;
    if (res < 0) res += p;
    return res;
}

// int main()
// {
//     cout << qpow(2, 5, 15);
// }