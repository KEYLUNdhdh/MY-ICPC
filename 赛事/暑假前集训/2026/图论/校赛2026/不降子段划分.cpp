#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
struct node
{
    int l, r, val;
};
void solve()
{
    int n;
    cin >> n;
    vector<node> a(n);
    int drop = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i].val;
        if(i > 0 && a[i].val < a[i - 1].val)
            drop++;
    }
    vector<int> p(n);
    for (int i = 0; i < n;i++)
    {
        cin >> p[i];
        p[i]--;
    }
    for (int i = 0; i < n;i++)
    {
        a[i].l = i - 1;
        a[i].r = i + 1;
    }
    for (int i = 0; i < n;i++)
    {
        cout << drop + 1 << " ";
        int pos = p[i];
        int l = a[pos].l;
        int r = a[pos].r;
        if(l >= 0 && a[l].val > a[pos].val)
            drop--;
        if(r < n && a[r].val < a[pos].val)
            drop--;
        if(l >= 0 && r < n && a[l].val > a[r].val)
            drop++;
        if(l >= 0)
            a[l].r = a[pos].r;
        if(r < n)
            a[r].l = a[pos].l;
    }
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}