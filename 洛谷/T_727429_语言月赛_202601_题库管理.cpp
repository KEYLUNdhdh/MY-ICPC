#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k;
const int MAXN = 5e3 + 5;
vector<int> a[55];
int pos[MAXN];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= m;i++)
    {
        a[0].push_back(i);
        pos[i] = 0;
    }
    int op, u, v;
    while(k--)
    {
        cin >> op >> u >> v;
        if(op == 1)
        {
            auto it = lower_bound(a[pos[u]].begin(), a[pos[u]].end(), u);
            int k = *it;
            a[pos[u]].erase(it);
            auto ii = lower_bound(a[v].begin(), a[v].end(), k);
            pos[u] = v;
            a[v].insert(ii, k);
        }
        else
        {
            if(a[v].size() < u)
            {
                cout << -1 << "\n";
                continue;
            }
            cout << a[v][u - 1] << "\n";
        }
    }
}