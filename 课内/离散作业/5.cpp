#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

// i128 输出重载
ostream &operator<<(ostream &os, i128 n) 
{
    string s;
    if(n == 0) s = "0";
    if(n < 0) 
    {
        s += "-";
        n = -n;
    }
    while (n) 
    {
        s += '0' + (i64)(n % 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

// i128 输入重载
istream &operator>>(istream &is, i128& n) 
{
    n = 0; string s; is >> s;
    bool neg = (s[0] == '-');
    for (int i = neg ? 1 : 0; i < s.size(); i++) 
        n = n * 10 + s[i] - '0';
    if(neg) 
        n = -n;
    return is;
}

// 扩展欧几里得算法用于求逆元
i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) 
{
    if (b == 0) 
    {
        x = 1; y = 0;
        return a;
    }
    i128 g = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

// 基于 exgcd 求模逆元
i128 get_inv(i128 a, i128 m) {
    i128 x, y;
    i128 g = exgcd(a, m, x, y);

    if (g != 1) 
        return -1; // 不互质，不存在逆元

    return (x % m + m) % m; // 转化为最小正整数解
}

// 快速幂：计算 (base^exp) % mod
i128 qpow(i128 base, i128 exp, i128 mod) {
    i128 res = 1;
    base %= mod;
    while (exp > 0) 
    {
        if (exp % 2 == 1) 
            res = (res * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// 解决单组测试数据的核心函数
void solve() 
{
    i128 p, q, e, m;
    cin >> p >> q >> e >> m;

    i128 n = p * q;
    i128 phi = (p - 1) * (q - 1);

    // 1. 生成私钥 d
    i128 d = get_inv(e, phi);
    if (d == -1) 
    {
        cout << "Error: gcd(e, phi) != 1\n";
        return;
    }

    cout << "--- Key Generation ---\n";
    cout << "n      = " << n << "\n";
    cout << "phi(n) = " << phi << "\n";
    cout << "Public Key (n, e) : (" << n << ", " << e << ")\n";
    cout << "Private Key (n, d): (" << n << ", " << d << ")\n";

    // 2. 加密
    i128 c = qpow(m, e, n);
    cout << "\n--- Encryption ---\n";
    cout << "Ciphertext c = " << c << "\n";

    // 3. 解密
    i128 m_prime = qpow(c, d, n);
    cout << "\n--- Decryption ---\n";
    cout << "Decrypted m' = " << m_prime << "\n\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    if (cin >> T) 
    {
        for (int i = 1; i <= T; i++) 
        {
            cout << "========== Test Case " << i << " ==========\n";
            solve();
        }
    }
    
    return 0;
}