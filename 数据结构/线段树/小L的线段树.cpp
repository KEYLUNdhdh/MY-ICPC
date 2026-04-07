#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
#define lyc_fan_club main
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
const int MOD = 998244353;
const int P = 998244353;
struct SegmentTree {
    int n;
    std::vector<int> tag, sum, bro;
    SegmentTree(int n_) : n(n_), tag(4 * n + 5, 1), sum(4 * n + 5, 1) ,bro(4 * n + 1,0) {}
    
    int query(int p, int l, int r, int x, int y) 
    {
        if(l >= x && r <= y)
            return sum[p];
        int m = (l + r) >> 1;
        if (!bro[p]) {
            int res = 1;
            if (x <= m) res += query(p << 1, l, m, x, y);
            if (y > m) res += query(p << 1 | 1, m + 1, r, x, y);
            return res;
        } else {
            int res = 0;
            if (x <= m) res += query(p << 1, l, m, x, y);
            if (y > m) res += query(p << 1 | 1, m + 1, r, x, y);
            return res;
        }
    }
    
    int query(int x, int y) 
    {
        return query(1, 1, n, x, y);
    }

    void de(int p, int l, int r, int x, int y)
    {
        if(l == x && r == y)
        {
            if(bro[p])
                return;
            bro[p] = 1;
            if(l == r)
            {
                sum[p] = 0;
            }
            else
            {
                sum[p] = sum[2 * p] + sum[2 * p + 1];
            }
            return;
        }
        else if(l > y || r < x)
            return;
        int m = l + r >> 1;
        if(y <= m)
            de(2 * p, l, m, x, y);
        else
            de(2 * p + 1, m + 1, r, x, y);
        if(bro[p])
        //节点坏了，下面有调整，我们要更新
            sum[p] = sum[2 * p] + sum[2 * p + 1];
        else
        //否则，我们只要访问到这个节点就可以终止，该节点仍为1
            sum[p] = 1;
    }
};
void solve()
{
    int n;
    cin >> n;
    SegmentTree sg(n);
    int t = n;
    while(t--)
    {
        int o, l, r;
        cin >> o >> l >> r;
        if(o == 1)
        {
            sg.de(1, 1, n, l, r);
        }
        else
        {
            cout << sg.query(l, r) << "\n";
        }
    }
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}