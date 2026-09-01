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
// https://codeforces.com/gym/705657
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
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

struct SegmentTree
{
    int n;
    vector<array<i64, 10>> tr1, tr2, tag;

    SegmentTree(int n_) : n(n_), tr1(4 * n + 1, {0}), tr2(4 * n + 1, {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}), tag(4 * n + 1, {0}) {}

    void pull(int p)
    {
        for (int i = 0; i < 10;i++)
        {
            tr1[p][i] = min(tr1[p << 1][i], tr1[p << 1 | 1][i]);
            tr2[p][i] = min(tr2[p << 1][i], tr2[p << 1 | 1][i]);
        }
    }

    void applyAdd(int p, int id, int v)
    {
        tr1[p][id] += v;
        tag[p][id] += v;
    }

    void push(int p)
    {
        for (int i = 0; i < 10;i++)
        {
            if(tag[p][i] != 0)
            {
                applyAdd(p << 1, i, tag[p][i]);
                applyAdd(p << 1 | 1, i, tag[p][i]);
                tag[p][i] = 0;
            }
        }
    }

    void rangeAdd(int p, int l, int r, int x, int y, int id, int v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applyAdd(p, id, v);
            return;
        }

        push(p);
        int m = l + r >> 1;
        rangeAdd(p << 1, l, m, x, y, id, v);
        rangeAdd(p << 1 | 1, m + 1, r, x, y, id, v);
        pull(p);
    }

    void rangeAdd(int x, int y, int id, int v)
    {
        rangeAdd(1, 1, n, x, y, id, v);
    }

    void flip(int p, int l, int r, int pos)
    {
        if(l == r)
        {
            for (int i = 0; i < 10;i++)
                swap(tr1[p][i], tr2[p][i]);
            return;
        }
        int m = l + r >> 1;
        push(p);
        if(pos <= m)
            flip(p << 1, l, m, pos);
        else
            flip(p << 1 | 1, m + 1, r, pos);
        pull(p);
    }

    void flip(int pos)
    {
        flip(1, 1, n, pos);
    }

    int queryMin(int p, int l, int r, int x, int y, int id)
    {
        if(l > y || r < x)
            return INF;
        if(l >= x && r <= y)
            return min(tr1[p][id], tr2[p][id]);

        push(p);
        int m = l + r >> 1;
        return min(queryMin(p << 1, l, m, x, y, id), queryMin(p << 1 | 1, m + 1, r, x, y, id));
    }

    int queryMin(int x, int y, int id)
    {
        return queryMin(1, 1, n, x, y, id);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    SegmentTree seg(n);
    auto get = [&](int x) -> array<i64, 10>
    {
        array<i64, 10> res{0};
        for (int i = 0; i < 10;i++)
        {
            while(x % primes[i] == 0)
                x /= primes[i], res[i]++;
        }
        return res;
    };

    while(m--)
    {
        string s;cin >> s;
        if(s == "mul")
        {
            int l, r, x;
            cin >> l >> r >> x;
            auto res = get(x);
            for (int i = 0; i < 10;i++)
                seg.rangeAdd(l, r, i, res[i]);
        }
        else if(s == "div")
        {
            int l, r, x;
            cin >> l >> r >> x;
            auto res = get(x);
            int f = 1;
            for (int i = 0; i < 10;i++)
            {
                i64 minn = seg.queryMin(l, r, i);
                if(minn < res[i])
                {
                    cout << "NO\n";
                    f = 0;
                    break;
                }
            }
            if(!f)
                continue;
            cout << "YES\n";
            for (int i = 0; i < 10;i++)
                seg.rangeAdd(l, r, i, -res[i]);
        }
        else
        {
            int pos;
            cin >> pos;
            seg.flip(pos);
        }
    }
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}