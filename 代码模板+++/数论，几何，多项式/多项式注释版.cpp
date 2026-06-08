#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const i64 MOD = 998244353;
const int G = 3;// 998244353的原根

// 快速幂
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

// ---------------- 底层变换：NTT ----------------
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

    void transform(vector<i64> &a, int flag)
    {
        int n = a.size();

        initRev(n);
        for(int i = 0;i < n;i++)
            if(i < rev[i])
                swap(a[i], a[rev[i]]);

        for (int mid = 1; mid < n;mid <<= 1)
        {
            i64 wn = qpow(G, (MOD - 1) / (mid << 1));
            if(flag == -1)
                wn = qpow(wn, MOD - 2);

            for (int i = 0; i < n;i += (mid << 1))
            {
                i64 w = 1;
                for (int j = 0; j < mid;j++, w = w * wn % MOD)
                {
                    i64 x = a[i + j];
                    i64 y = w * a[i + j + mid] % MOD;
                    a[i + j] = (x + y >= MOD ? x + y - MOD : x + y);
                    a[i + j + mid] = (x - y < 0 ? x - y + MOD : x - y);
                }
            }
        }

        if(flag == -1)
        {
            i64 invN = qpow(n, MOD - 2);
            for (int i = 0; i < n;i++)
                a[i] = a[i] * invN % MOD;
        }
    }
}

// ---------------- 高层结构：多项式对象 ----------------
struct Poly
{
    vector<i64> a;

    // 构造函数
    Poly() {}
    Poly(int size) : a(size, 0) {}
    Poly(const vector<i64> &a_) : a(a_) {}
    Poly(initializer_list<i64> a_) : a(a_) {}

    int size() const { return a.size(); }
    void resize(int n) { a.resize(n); }

    // 安全访问
    i64 operator[](int idx) const { return idx < size() ? a[idx] : 0; }
    i64 &operator[](int idx) { return a[idx]; }

    // 截取前 k 项 (mod x^k)
    Poly modXk(int k) const
    {
        k = min(k, size());
        return Poly(vector<i64>(a.begin(), a.begin() + k));
    }

    // 乘以 x^k (整体右移)
    Poly mulXk(int k) const
    {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }

    // 多项式加法
    friend Poly operator+(const Poly &A, const Poly &B)
    {
        Poly res(max(A.size(), B.size()));
        for (int i = 0; i < res.size(); i++)
            res[i] = (A[i] + B[i]) % MOD;
        return res;
    }

    // 多项式减法
    friend Poly operator-(const Poly &A, const Poly &B)
    {
        Poly res(max(A.size(), B.size()));
        for (int i = 0; i < res.size(); i++)
            res[i] = (A[i] - B[i] + MOD) % MOD;
        return res;
    }

    // 乘法：调用底层 NTT
    friend Poly operator*(Poly A, Poly B)
    {
        if(A.size() == 0 || B.size() == 0)
            return Poly();

        int n = A.size(), m = B.size();
        int limit = 1;
        while(limit < n + m - 1)
            limit <<= 1;

        A.resize(limit);
        B.resize(limit);
        NTT::transform(A.a, 1);
        NTT::transform(B.a, 1);
        for (int i = 0; i < limit;i++)
            A[i] = A[i] * B[i] % MOD;

        NTT::transform(A.a, -1);
        A.resize(n + m - 1);
        return A;
    }

    // 与常数乘法
    friend Poly operator*(Poly A, i64 k)
    {
        k = (k % MOD + MOD) % MOD;
        for (int i = 0; i < A.size();i++)
            A[i] = A[i] * k % MOD;
        return A;
    }

    // 求导
    Poly deriv() const
    {
        if(size() <= 1)
            return Poly({0});
        Poly res(size() - 1);
        for (int i = 1;i < size(); i++)
            res[i - 1] = a[i] * i % MOD;
        return res;
    }

    // 积分
    Poly integr() const
    {
        Poly res(size() + 1);
        for (int i = 0; i < size();i++)
            res[i + 1] = a[i] * qpow(i + 1, MOD - 2) % MOD;
        return res;
    }

    // 求逆：B = B * (2 - A * B) mod x^deg
    Poly inv(int deg) const 
    {
        Poly res({qpow(a[0], MOD - 2)});
        int k = 1;
        while(k < deg)
        {
            k <<= 1;
            Poly cur = modXk(k);// A 的前 k 项
            res = (res * (Poly({2}) - cur * res)).modXk(k);// 因为重载了运算符，这里的代码极其优雅且符合直觉！
        }
        return res.modXk(deg);
    }

    // 求对数 Ln：∫(A' / A) dx
    Poly ln(int deg) const
    {
        return (deriv() * inv(deg)).integr().modXk(deg);
    }

    // 求指数 Exp：B = B * (1 - ln(B) + A) mod x^deg
    Poly exp(int deg) const 
    {
        // 题目保证了 a[0] = 0，而 e^0 = 1，所以常数项初始化为 1    
        Poly res({1});
        int k = 1;
        while(k < deg)
        {
            k <<= 1;
            Poly cur = modXk(k);// 截取 A 的前 k 项
            // 完美复刻牛顿迭代公式
            res = (res * (Poly({1}) - res.ln(k) + cur)).modXk(k);
        }
        return res;
    }
};