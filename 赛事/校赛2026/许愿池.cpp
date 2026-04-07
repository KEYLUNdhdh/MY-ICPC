#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 qpow(i64 a, i64 b, i64 p)
{
    i64 res = 1;
    a %= p;
    while(b)
    {
        if(b & 1)
            res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res % p;
}

i64 bi(i64 a, i64 n, i64 c)
{
    if(n == 1)
        return a;
    if(n % 2 == 0)
    {
        i64 mid = n / 2;
        i64 lhs = 1 + qpow(a, mid, c);
        return lhs * bi(a, mid, c) % c;
    }
    else
    {
        i64 real = n - 1;
        i64 mid = real / 2;
        i64 lhs = 1 + qpow(a, mid, c);
        return (lhs * bi(a, mid, c) % c + qpow(a, n, c)) % c;
    }
}
void solve()
{
    i64 x, a, n, c;
    cin >> x >> a >> n >> c;
    i64 pow = qpow(a, n, c);
    i64 lst = bi(a, n, c);
    i64 ans = pow * x % c - lst % c;
    cout << (ans % c + c) % c << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}