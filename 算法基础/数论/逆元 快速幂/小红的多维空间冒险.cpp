#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
int inverse[MAXN + 5];
int c[MAXN];
void g(int p)
{
    inverse[1] = 1;
    for (int i = 2; i < MAXN;i++)
    {
        inverse[i] = (p - p / i) * inverse[p % i] % p;
    }
}
int poww(int a,int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;

    }
    return res;
}
signed main()
{
    int n;
    cin >> n;
    g(MOD);
    c[0] = 1;
    int up = poww(2, n - 1);
    for (int i = 1; i <= n;i++)
    {
        c[i] = c[i - 1] * (n - i + 1) % MOD;
        c[i] = c[i] * inverse[i] % MOD;
        cout << c[i] * up % MOD << " ";
    }
}