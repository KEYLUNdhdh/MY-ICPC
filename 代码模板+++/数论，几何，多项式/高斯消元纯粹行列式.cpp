#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

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

const i64 MOD = 998244353;

struct Gauss
{
    Gauss() {}
    
    i64 calc(vector<vector<i64>> a)
    {
        int n = a.size();
        i64 det = 1;

        for (int i = 0; i < n;i++)
        {
            int pivot = i;
            for (int j = i;j < n;j++)
            {
                if(a[j][i] != 0)
                {
                    pivot = j;
                    break;
                }
            }

            if(a[pivot][i] == 0)
                return 0;

            if(pivot != i)
            {
                swap(a[i], a[pivot]);
                det = (MOD - det) % MOD;
            }

            det = det * a[i][i] % MOD;
            i64 in = inv(a[i][i], MOD);

            for (int j = i + 1; j < n; j++)
            {
                if(a[j][i] == 0)
                    continue;

                i64 factor = a[j][i] * in % MOD;
                for (int k = i; k < n;k++)
                {
                    a[j][k] = (a[j][k] - factor * a[i][k]) % MOD;
                    if(a[j][k] < 0)
                        a[j][k] += MOD;
                }
            }
        }
        return (det % MOD + MOD) % MOD;
    }
};