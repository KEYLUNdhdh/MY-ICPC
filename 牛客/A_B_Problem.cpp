//nowcoder
#include <bits/stdc++.h>
#define int long long
#define ld long double
using namespace std;
const int MOD = 998244353;
int qpow(int a,int b)
{
    a %= MOD;
    int res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}
int inv(int a)
{
    return qpow(a, MOD - 2);
}
int c;
int pd[10];

int se[10][7] = {
    {1, 1, 1, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}
};


int cal(int x)
{
    string k = to_string(x);
    while(k.size() < 4)
    {
        k = "0" + k;
    }
    int res = 1;
    for(auto i : k)
    {
        res = res * pd[i - '0'] % MOD;
    }
    return res;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    int i100 = inv(100);
    while(t--)
    {
        vector<int> p(8);
        cin >> c;
        for (int i = 1; i <= 7;i++)
        {
            int tp;
            cin >> tp;
            p[i] = tp * i100 % MOD;
        }
        for (int i = 0; i <= 9;i++)
        {
            int pdd = 1;
            for (int j = 0; j < 7;j++)
            {
                if(se[i][j])
                {
                    pdd = pdd * p[j + 1] % MOD;
                }
                else
                {
                    int poff = (1 - p[j + 1] + MOD) % MOD;
                    pdd = pdd * poff % MOD;
                }
            }
            pd[i] = pdd;
        }
        int ans = 0;
        for (int i = 0; i <= c;i++)
        {
            ans += cal(i) * cal(c - i) % MOD;
        }
        cout << ans % MOD << "\n";
    }
}