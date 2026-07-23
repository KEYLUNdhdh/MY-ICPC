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
static constexpr int MAXK = 3;
struct Point
{
    array<i64, MAXK> x{};
    i64 v = 0;
};


struct KDTree
{

    struct Node
    {
        int ls = 0, rs = 0;
        array<i64, MAXK> minn{}, maxx{};
        Point p{};
        i64 sum = 0, lazy = 0;
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
        tr[u].sum = p.v;
        tr[u].sz = 1;
        return u;
    }

    void pushUp(int u)
    {
        int l = tr[u].ls, r = tr[u].rs;
        tr[u].sz = tr[l].sz + tr[r].sz + 1;
        tr[u].sum = tr[l].sum + tr[r].sum + tr[u].p.v;

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

    void apply(int u, i64 v)
    {
        if(!u)
            return;
        
        tr[u].p.v += v;
        tr[u].sum += v * tr[u].sz;
        tr[u].lazy += v;
    }

    void pushDown(int u)
    {
        if(tr[u].lazy)
        {
            apply(tr[u].ls, tr[u].lazy);
            apply(tr[u].rs, tr[u].lazy);
            tr[u].lazy = 0;
        }
    }

    void flatten(int u)
    {
        if(!u)
            return;

        pushDown(u);
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

        pushDown(u);
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

    bool isPointInside(const Point &p, const Point &A, const Point &B)
    {
        for (int i = 0; i < k;i++)
            if(p.x[i] < A.x[i] || p.x[i] > B.x[i])
                return false;

        return true;
    }

    // -1：不相交
    //  0：部分相交
    //  1：完全包含
    int relation(int u, const Point &A, const Point &B) const
    {
        bool inside = true;

        for(int i = 0; i < k; i++)
        {
            if(tr[u].maxx[i] < A.x[i] || tr[u].minn[i] > B.x[i])
                return -1;

            if(tr[u].minn[i] < A.x[i] || tr[u].maxx[i] > B.x[i])
                inside = false;
        }

        return inside ? 1 : 0;
    }

    void _modify(int u, const Point &A, const Point &B, i64 v)
    {
        if(!u)
            return;

        int rel = relation(u, A, B);

        if(rel == -1)
            return;

        if(rel == 1)
        {
            apply(u, v);
            return;
        }

        pushDown(u);
        if(isPointInside(tr[u].p, A, B))
            tr[u].p.v += v;

        _modify(tr[u].ls, A, B, v);
        _modify(tr[u].rs, A, B, v);
        pushUp(u);
    }

    i64 _query(int u, const Point &A, const Point &B)
    {
        if(!u)
            return 0;

        int rel = relation(u, A, B);

        if(rel == -1)
            return 0;
        if(rel == 1)
            return tr[u].sum;

        pushDown(u);
        i64 res = 0;
        if(isPointInside(tr[u].p, A, B))
            res += tr[u].p.v;

        res += _query(tr[u].ls, A, B);
        res += _query(tr[u].rs, A, B);
        return res;
    }

    void insert(const Point &p) { _insert(root, p, 0); }
    void modify(const Point &A, const Point &B, i64 v) { _modify(root, A, B, v); }
    i64 query(const Point &A, const Point &B) { return _query(root, A, B); }
};

void solve()
{
    int k, m;
    cin >> k >> m;

    KDTree kd(k);

    i64 lst = 0;
    while(m--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            Point A;
            for (int i = 0; i < k;i++)
                cin >> A.x[i], A.x[i] ^= lst;

            cin >> A.v;
            A.v ^= lst;
            kd.insert(A);
        }
        else if(op == 2)
        {
            Point A, B;
            for (int i = 0; i < k;i++)
                cin >> A.x[i], A.x[i] ^= lst;
            for (int i = 0; i < k;i++)
                cin >> B.x[i], B.x[i] ^= lst;
            i64 v;
            cin >> v;
            v ^= lst;

            kd.modify(A, B, v);
        }
        else
        {
            Point A, B;
            for (int i = 0; i < k;i++)
                cin >> A.x[i], A.x[i] ^= lst;
            for (int i = 0; i < k;i++)
                cin >> B.x[i], B.x[i] ^= lst;

            i64 ans = kd.query(A, B);
            lst = ans;
            cout << ans << "\n";
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