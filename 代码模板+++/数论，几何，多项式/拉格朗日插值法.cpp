#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

const i64 MOD = 998244353;

template<class T>
T qpow(T a,T b,T MOD)
{
    T res = 1;
    a = (a % MOD + MOD) % MOD;
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
T inv(T a,T p)
{
    return qpow(a, p - 2, p);
}

struct Lagrange
{
    int n;
    vector<i64> x, y;

    Lagrange() : n(0) {}

    void addPoint(i64 px, i64 py)
    {
        x.push_back(px);
        y.push_back(py);
        n++;
    }

    i64 query(i64 k)
    {
        k = (k % MOD + MOD) % MOD;
        i64 ans = 0;
        for (int i = 0;i < n;i++)
        {
            i64 num = 1;
            i64 den = 1;

            for (int j = 0;j < n;j++)
            {
                if(i == j)
                    continue;

                num = num * (k - x[j] + MOD) % MOD;
                den = den * (x[i] - x[j] + MOD) % MOD;
            }

            i64 term = y[i] * num % MOD * inv(den, MOD) % MOD;
            ans = (ans + term) % MOD;
        }
        return ans;
    }
};