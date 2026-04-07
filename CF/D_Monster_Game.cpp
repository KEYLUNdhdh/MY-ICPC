#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
const int INF = 2e18;
int a[MAXN], b[MAXN];
int prefixb[MAXN];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n;i++)
            cin >> a[i];
        for (int i = 1; i <= n;i++)
            cin >> b[i];
        sort(a + 1, a + n + 1, [](int x, int y)
             { return x > y; });
        int need = 0;
        int maxx = 0;
        for (int i = 1; i <= n;i++)
        {
            need += b[i];
            if(need > n)
                break;
            int dif = a[need];
            int level = i;
            maxx = max(dif * level, maxx);
        }
        cout << maxx << "\n";
    }
}