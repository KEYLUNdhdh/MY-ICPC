#include <bits/stdc++.h>
using namespace std;

int phi(int n)
{
    int res = n;
    for (int i = 2; i * i <= n;i++)
    {
        if(n % i == 0)
        {
            while(n % i == 0)
                n /= i;
            res = res / i * (i - 1);
        }
    }
    if(n > 1)
        res = res / n * (n - 1);
    return res;
}

namespace sieve
{
    int n;
    vector<int> primes;
    vector<int> phi, mu, vis;

    void init(int n_)
    {
        n = n_;
        primes.clear();
        phi.assign(n + 1, 0);
        mu.assign(n + 1, 0);
        vis.assign(n + 1, 0);
    }

    void run()
    {
        phi[1] = 1;
        mu[1] = 1;
        for (int i = 2; i <= n;i++)
        {
            if(!vis[i])
            {
                primes.push_back(i);
                phi[i] = i - 1;
                mu[i] = -1;
            }

            for(int p : primes)
            {
                if(1ll * i * p > n)
                    break;

                int x = i * p;
                vis[x] = 1;

                if(i % p == 0)
                {
                    phi[x] = phi[i] * p;
                    mu[x] = 0;
                    break;
                }
                else
                {
                    phi[x] = phi[i] * (p - 1);
                    mu[x] = -mu[i];
                }
            }
        }
    }
}

