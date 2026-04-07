#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
#define int long long
int ro[MAXN];
int prefix[MAXN];
int n, m;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int r, s;
    for (int i = 1; i <= n;i++)
    {
        cin >> r >> s;
        ro[i] = r * s;
        prefix[i] = prefix[i - 1] + ro[i];
    }
    int cnt = lower_bound(prefix + 1, prefix + 1 + n, m) - prefix;
    cout << cnt * 2;
}