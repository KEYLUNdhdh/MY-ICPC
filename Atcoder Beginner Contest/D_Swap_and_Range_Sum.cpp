#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int tree[MAXN];
int n, q;
inline int lowbit(int x)
{
    return x & (-x);
}

void add(int x,int k)
{
    while (x <= n)
    {
        tree[x] += k;
        x += lowbit(x);
    }
}

int query(int x)
{
    int res = 0;
    while(x > 0)
    {
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}
int a[MAXN];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;
    int val;
    for (int i = 1; i <= n;i++)
    {
        cin >> val;
        a[i] = val;
        add(i, val);
    }
    int op, x, l, r;
    while(q--)
    {
        cin >> op;
        if(op == 1)
        {
            cin >> x;
            int d = a[x + 1] - a[x];
            add(x, d);
            add(x + 1, -d);
            int tp = a[x];
            a[x] = a[x + 1];
            a[x + 1] = tp;
        }
        else
        {
            cin >> l >> r;
            cout << query(r) - query(l - 1) << "\n";
        }
    }
}