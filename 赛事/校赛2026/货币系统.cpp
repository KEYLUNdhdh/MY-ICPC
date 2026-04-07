#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline {cerr << "----------------------\n";}
using namespace std;
using i64 = long long;
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    vector<int> f(a[n], 0);
    f[0] = 0;
    for (int i = 1; i < a[n];i++)
    {
        auto it = upper_bound(a.begin(), a.end(), i);
        i64 k;
        if(it == a.begin())
            k = 0;
        else
        {
            it--;
            k = *it;
        }
        f[i] = 1 + f[i - k];
    }
    sort(f.begin(), f.end());
    // debugarr(f)
    while (q--)
    {
        int m;
        cin >> m;
        auto it = upper_bound(f.begin(), f.end(), m);
        cout << it - f.begin() << " ";
    }
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