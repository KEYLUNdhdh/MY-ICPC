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
constexpr i64 MOD = 998244353, INF = 2e18;

static constexpr int MAXK = 2;
struct Point
{
    array<ld, MAXK> x{};
    ld dis2(const Point &a) const { return (x[0] - a.x[0]) * (x[0] - a.x[0]) + (x[1] - a.x[1]) * (x[1] - a.x[1]); }
};


struct KDTree
{

    struct Node
    {
        int ls = 0, rs = 0;
        array<ld, MAXK> minn{}, maxx{};
        Point p{};
        int sz = 0;
    };

    int k;
    int root;
    ld alpha;
    vector<Node> tr;
    vector<int> flatNodes;

    KDTree(int k_, int reserveSize = 2e5) : k(k_), root(0), alpha(0.75)
    {
        assert(k >= 1 && k <= MAXK);
        tr.reserve(reserveSize + 1);
        tr.emplace_back();
        flatNodes.reserve(reserveSize);
    }

    int newNode(const Point &p)
    {
        int u = tr.size();
        tr.emplace_back();
        tr[u].p = p;
        tr[u].maxx = tr[u].minn = p.x;
        tr[u].sz = 1;
        return u;
    }

    void pushUp(int u)
    {
        int l = tr[u].ls, r = tr[u].rs;
        tr[u].sz = tr[l].sz + tr[r].sz + 1;

        for (int i = 0; i < k;i++)
        {
            tr[u].minn[i] = tr[u].maxx[i] = tr[u].p.x[i];
            if(l)
            {
                tr[u].minn[i] = min(tr[u].minn[i], tr[l].minn[i]);
                tr[u].maxx[i] = max(tr[u].maxx[i], tr[l].maxx[i]);

            }
            if(r)
            {
                tr[u].minn[i] = min(tr[u].minn[i], tr[r].minn[i]);
                tr[u].maxx[i] = max(tr[u].maxx[i], tr[r].maxx[i]);
            }
        }
    }

    void flatten(int u)
    {
        if(!u)
            return;

        flatten(tr[u].ls);
        flatNodes.push_back(u);
        flatten(tr[u].rs);
    }

    int build(int l, int r, int dim)
    {
        if(l > r)
            return 0;

        int m = l + r >> 1;
        nth_element(flatNodes.begin() + l, flatNodes.begin() + m, flatNodes.begin() + r + 1, [&](int a, int b) { return tr[a].p.x[dim] < tr[b].p.x[dim]; });

        int u = flatNodes[m];
        tr[u].ls = build(l, m - 1, (dim + 1) % k);
        tr[u].rs = build(m + 1, r, (dim + 1) % k);
        pushUp(u);
        return u;
    }

    void checkRebuild(int &u, int dim)
    {
        if(tr[tr[u].ls].sz > alpha * tr[u].sz || tr[tr[u].rs].sz > alpha * tr[u].sz)
        {
            flatNodes.clear();
            flatten(u);
            u = build(0, flatNodes.size() - 1, dim);
        }
    }

    void _insert(int &u, const Point &p, int dim)
    {
        if(!u)
        {
            u = newNode(p);
            return;
        }

        if(p.x[dim] <= tr[u].p.x[dim])
        {
            int ls = tr[u].ls;
            _insert(ls, p, (dim + 1) % k);
            tr[u].ls = ls;
        }
        else
        {
            int rs = tr[u].rs;
            _insert(rs, p, (dim + 1) % k);
            tr[u].rs = rs;
        }
        
        pushUp(u);
        checkRebuild(u, dim);
    }

    ld getDis(int u, const Point &A, int f) const
    {
        if(f) // Max
        {
            ld mnx = tr[u].minn[0], mxx = tr[u].maxx[0];
            ld mny = tr[u].minn[1], mxy = tr[u].maxx[1];
            ld tx = max(fabsl(A.x[0] - mnx), fabsl(A.x[0] - mxx));
            ld ty = max(fabsl(A.x[1] - mny), fabsl(A.x[1] - mxy));
            return tx * tx + ty * ty;
        }
        else // Min
        {
            ld res = 0;
            for (int i = 0; i < k;i++)
            {
                ld d = 0;
                if(A.x[i] < tr[u].minn[i])
                    d = tr[u].minn[i] - A.x[i];
                else if(A.x[i] > tr[u].maxx[i])
                    d = A.x[i] - tr[u].maxx[i];
                res += d * d;
            }
            return res;
        }
    }


    ld _queryMax(int u, const Point &A, ld &ans)
    {
        if(!u)
            return 0;

        ld dis = getDis(u, A, 1);
        if(dis <= ans)
            return 0;

        ld res = A.dis2(tr[u].p);
        chmax(ans, res);
        chmax(res, _queryMax(tr[u].ls, A, ans));
        chmax(res, _queryMax(tr[u].rs, A, ans));
        chmax(ans, res);
        return res;
    }

    ld _queryMin(int u, const Point &A, ld &ans)
    {
        if(!u)
            return INF;

        ld dis = getDis(u, A, 0);
        if(dis > ans)
            return INF;

        ld res = A.dis2(tr[u].p);
        chmin(ans, res);// 可以剪掉更多搜索
        chmin(res, _queryMin(tr[u].ls, A, ans));
        chmin(res, _queryMin(tr[u].rs, A, ans));
        return res;
    }

    void insert(const Point &p) { _insert(root, p, 0); }
    ld queryMax(const Point &A, ld &ans) { return _queryMax(root, A, ans); }
    ld queryMin(const Point &A, ld &ans) { return _queryMin(root, A, ans); }

};

void solve()
{
    int n;
    cin >> n;

    KDTree kd(2);
    ld minn = INF, maxx = 0;
    for (int i = 0; i < n;i++)
    {
        Point a;
        cin >> a.x[0] >> a.x[1];
        kd.queryMax(a, maxx);
        kd.queryMin(a, minn);
        kd.insert(a);
    }
    cout << fixed << setprecision(2) << sqrtl(minn) << " " << sqrtl(maxx);
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