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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

struct DSU
{
    vector<int> f, siz;
    vector<pii> his;
    DSU() {}
    DSU(int n)
    {
        init(n);
    }
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        his.clear();
    }
    int find(int x)
    {
        while(x != f[x])
            x = f[x];
        return x;
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(siz[x] < siz[y])
            swap(x, y);
        his.push_back({y, x});
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
    void undo()
    {
        if(his.empty())
            return;
        auto [y, x] = his.back();
        his.pop_back();
        siz[x] -= siz[y];
        f[y] = y;
    }
    int hissize()
    {
        return his.size();
    }
    void rollback(int tag)
    {
        while(his.size() > tag)
            undo();
    }
};

struct e
{
    int u, v, id;
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<e> edges(m);
    vector<int> ans(m + 1, 0);
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        edges[i].u = u, edges[i].v = v;
        edges[i].id = i + 1;
    }

    if (m < 3)
    {
        if(m == 1)
            cout << "0";
        else
            cout << "01";
        cout << "\n";
        return;
    }

    int turn = 0;
    while(1)
    {
        int f = 1;
        turn++;
        DSU dsu1(n), dsu2(n);
        shuffle(edges.begin(), edges.end(), rnd);
        for (int i = 0; i < m;i++)
        {
            auto &[u, v, id] = edges[i];
            if(!dsu1.same(u, v))
                dsu1.merge(u, v);
            else if (!dsu2.same(u, v))
                dsu2.merge(u, v), ans[id] = turn;
            else
            {
                f = 0;
                break;
            }
        }
        if(f)
            break;
    }
    
    for (int i = 1; i <= m;i++)
        if(ans[i] == turn)
            cout << 1;
        else
            cout << 0;
    cout << "\n";
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}