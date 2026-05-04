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
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937 rnd(time(0));

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
constexpr int MOD = 998244353, INF = 1e9;

struct SegmentTree {
    int n;
    std::vector<int> addTag, sum, minn;
    SegmentTree(int n_) : n(n_), addTag(4 * n + 1, 0), sum(4 * n + 1, 0), minn(4 * n + 1, 0) {}

    void pull(int p) 
    {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        minn[p] = min(minn[p << 1], minn[p << 1 | 1]);
    }

    void applyAdd(int p, int v) 
    {
        addTag[p] += v;
        sum[p] += v ;
        minn[p] += v;
    }

    void push(int p) 
    {
        if(addTag[p] != 0)
        {
            applyAdd(p << 1, addTag[p]);
            applyAdd(p << 1 | 1, addTag[p]);
            addTag[p] = 0;
        }
    }
    
    int rangeQuery(int p, int l, int r, int x, int y) 
    {
        if (l > y || r < x) 
        {
            return INF;
        }
        if (l >= x && r <= y) 
        {
            return minn[p];
        }
        int m = (l + r) / 2;
        push(p);
        return min(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m + 1, r, x, y));
    }
    
    int rangeQuery(int x, int y) 
    {
        return rangeQuery(1, 1, n, x, y);
    }
    
    void rangeAdd(int p, int l, int r, int x, int y, int v) 
    {
        if (l > y || r < x) 
        {
            return;
        }
        if (l >= x && r <= y)
        {
            return applyAdd(p, v);
        }
        int m = (l + r) / 2;
        push(p);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    
    void rangeAdd(int x, int y, int v) 
    {
        rangeAdd(1, 1, n, x, y, v);
    }
    
    
};
void solve()
{
    int n;
    cin >> n;
    vector<int> p(n + 1, 0), q(n + 1, 0);
    vector<int> pos(n + 1, -1);

    for (int i = 1; i <= n;i++)
    {
        cin >> p[i];
        pos[p[i]] = i;
    }
    for (int i = 1; i <= n;i++)
        cin >> q[i];
    SegmentTree sg(n + 1);
    int maxx = n;
    vector<int> ans(n);
    for (int i = 0; i < n;i++)
    {
        if(i == 0)
        {
            ans[i] = maxx;
            sg.rangeAdd(1, pos[maxx], -1);
            continue;
        }

        int block = q[i];
        sg.rangeAdd(1, block, 1);
        int minn = sg.rangeQuery(1, n);
        while(minn >= 0 && maxx >= 1)
        {
            maxx--;
            sg.rangeAdd(1, pos[maxx], -1);
            minn = sg.rangeQuery(1, n);
        }
        ans[i] = maxx;
    }
    for (int i = 0; i < n;i++)
        cout << ans[i] << " ";
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