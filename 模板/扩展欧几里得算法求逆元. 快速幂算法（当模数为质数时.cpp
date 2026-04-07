#include <bits/stdc++.h>
#define int long long
using namespace std;
// https://www.bilibili.com/video/BV195411w75c/?spm_id_from=333.337.search-card.all.click&vd_source=9fe037978f56e9671016c226acdbddbb
// 什么是逆元呢：对于a,b,p找到b_inverse,使得(a / b)(mod p) == (a * b_inverse)(mod p),称b_inverse 为b的逆元。经过进一步推理，有b * b_inverse == 1(mod p),当且仅当gcd(b , p) = 1时成立，可以利用这个式子求逆元
//  1. 扩展欧几里得算法函数
//  输入: a, b
//  输出: 返回 gcd(a, b)，同时通过引用修改 x 和 y，使得 ax + by = 1 = gcd(a, b)
// 这里所求的x就是a的逆元，b应该是模数
// 递推公式为 x = y'  /// y = x' - (a / b) * y'
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    // 递归调用
    // 注意这里传入的是 y 和 x 的位置，这是为了方便通过递归后的 x', y' 更新当前的 x, y
    // d 是最大公约数
    long long d = exgcd(b, a % b, y, x);
    
    // 根据推导公式: y = x' - (a/b) * y'
    // 在上一行递归中，参数位置交换了，所以这里的 y 其实是上一层的 x' (即递归后的结果存到了 y 变量里)
    // 这里的 x 其实是上一层的 y',y 其实是上一层的 x'
    // 所以更新逻辑是：
    y = y -  (a / b) * x; 
    
    return d;
}

// 2. 求逆元函数
// 求 a 在模 m 下的逆元
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = exgcd(a, m, x, y);
    
    // 如果 gcd(a, m) != 1，说明逆元不存在
    if (g != 1) {
        return -1; // 或者抛出异常
    }
    
    // ExGCD 求出的 x 可能是负数
    // 我们通常需要返回一个正数范围 [0, m-1] 的逆元
    return (x % m + m) % m;
}
//费马小定理，当p为质数时,对任意自然数，有pow(a,p - 1) == 1(mod p) 等价于 a * pow(a,p - 2) == 1(mod p),这里即求a的p - 2次，用快速幂.实际上为了防止ans过大，这里只用求a的p - 2次模p后的结果就行，此时ans依旧为a的逆元
//如果模数m为质数，则可以用快速幂求逆元
int fast_pow(int a,int b,int p)//pow(a,b)(mod p)
{
    int ans = 1;
    a = a % p;
    while (b)
    {
        if (b & 1)
            ans = ans * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}
int get_inv(int x, int p)//求x的逆元 
{
    return fast_pow(x, p - 2, p);
}
//3.线性数组去求逆元,假设现在相求x的inverse
// 对于一个数p = kx + r;k = (p / x)向下取整,r = p % x.
// 有kx + r = 0(mod p) 等价于 kx == -r(mod p) 又由于x * x_inverse = 1(mod p)
// 则有 k * r_inverse* x == -1 == (-1) * x * x_inverse(mod p).
// 最终有 x_inverse == （-1）*k * r_inverse(mod p)
//即 x_inverse == (p - k) * r_inverse(mod p)
//又因为 r = p % x,则r < x,按数组从小到大求,r_inverse 一定比x_inverse先求出，那么在求解x_inverse时就可以调用之前的r_inverse
const int maxn = 1e3 + 5;
int inverse[maxn] = {0};
void getinv_array(int n,int p)//求到第n，p为模数
{
    inverse[1] = 1;//1的逆元为1
    for (int i = 2; i <= n;i++)
    {
        // inverse[i] = (-1) * (p / i) * inverse[p % i];
        // inverse[i] = (inverse[i] % p + p) % p;//防止inv[i]为负数
        inverse[i] = (p - p / i) * inverse[p % i] % p;
        //这么写更快,更精准
    }
}
signed main()
{
    long long a, m;
    
    // 示例：求 3 在模 11 下的逆元
    // 预期结果：4 (因为 3 * 4 = 12，12 % 11 = 1)
    a = 3; 
    m = 11;
    
    cout << "Input: a = " << a << ", m = " << m << endl;
    
    long long inv = modInverse(a, m);
    
    if (inv == -1) {
        cout << "逆元不存在 (a 和 m 不互质)" << endl;
    } else {
        cout << a << " 在模 " << m << " 下的逆元是: " << inv << endl;
        
        // 验证
        cout << "验证: (" << a << " * " << inv << ") % " << m 
                  << " = " << (a * inv) % m << std::endl;
    }
    cout <<"快速幂算法求解："<< get_inv(a, m) << endl;
    getinv_array(3, 11);
    cout << "线性数组求逆元：" << inverse[3] << endl;
    return 0;
}