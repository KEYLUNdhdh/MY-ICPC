//nowcoder
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 998244353;
const int MAXN = 2e5 + 5;
int a[MAXN], b[MAXN];
int f[MAXN];
int n;
void ini()
{
    f[0] = 1;
    for (int i = 1; i < MAXN;i++)
    {
        f[i] = f[i - 1] * i % MOD;
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    ini();
    while(t--)
    {
        cin >> n;
        int minn = 0x3f3f3f3f;
        for (int i = 0; i < n;i++)
            cin >> a[i];
        for (int i = 0; i < n;i++)
        {
            cin >> b[i];
            minn = min(minn, b[i]);
        }
        int cntM = 0;
        int cntm = 0;
        for (int i = 0; i < n;i++)
        {
            if(a[i] > minn)
                cntM++;
            else
                cntm++;
        }
        cout << f[cntm] % MOD * f[cntM] % MOD << "\n";
    }
}