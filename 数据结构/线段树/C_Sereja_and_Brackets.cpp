#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr i64 MOD = 998244353, INF = 1e9;
int P = 998244353;
struct SegmentTree
{
    struct node
    {
        i64 sum, left, right;
    };
    int n;
    vector<node> vec;
    SegmentTree(int n_) : n{n_} , vec(4 * n + 1, {0, 0, 0}) {}

    void build(int p, int l, int r, const vector<int> &a)
    {
        if(l == r)
        {
            vec[p].sum = 0;
            if(a[l] == 1)
                vec[p].left = 1;
            else
                vec[p].right = 1;
            return;
        }

        int m = l + r >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        vec[p] = merge(vec[p << 1], vec[p << 1 | 1]);
    }

    node merge(node a, node b)
    {
        node res;
        int up = min(a.left, b.right);
        res.sum = up * 2 + a.sum + b.sum;
        res.left = a.left + b.left - up;
        res.right = a.right + b.right - up;
        return res;
    }

    node rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return {0, 0, 0};
        if(l >= x && r <= y)
            return vec[p];
        int m = l + (r - l) / 2;
       
        if(y <= m)
            return rangeQuery(p << 1, l, m, x, y);
        if(x >= m + 1)
            return rangeQuery(p << 1 | 1, m + 1, r, x, y);

        node ll = rangeQuery(p << 1, l, m, x, y);
        node rr = rangeQuery(p << 1 | 1, m + 1, r, x, y);

        return merge(ll, rr);
    }
    int rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y).sum;
    }
};


void solve()
{
    string s;
    cin >> s;

    int n;
    cin >> n;

    int len = s.size();
    vector<int> a(len + 1, 0);
    for (int i = 1; i <= len;i++)
    {
        if(s[i - 1] == '(')
            a[i] = 1;
        else
            a[i] = -1;
    }

    SegmentTree seg(len);
    seg.build(1, 1, len, a);
    for (int i = 0; i < n;i++)
    {
        int l, r;
        cin >> l >> r;
        cout << seg.rangeQuery(l, r) << "\n";
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