#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
i64 qpow(i64 a,i64 b,i64 MOD)
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
    return res % MOD;
}

i64 inv(i64 a,i64 p)
{
    return qpow(a, p - 2, p);
}
const i64 MOD = 998244353;
void solve()
{
    i64 n, a, b, y, p, q;
    cin >> n >> a >> b >> y >> p >> q;
    i64 k = a * inv(b, MOD) % MOD;
    i64 r = p * inv(q, MOD) % MOD;
    i64 lst = r * y % MOD;
    i64 up = k * r % MOD;
    i64 ans = 0;
    for (int i = 1; i <= n;i++)
        ans = (ans * up % MOD + lst) % MOD;
    cout << ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}