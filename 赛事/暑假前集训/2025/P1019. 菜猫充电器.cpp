#include <bits/stdc++.h>
#define lyc_fan_club main
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
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) // PII 
{
    return os << "(" << p.first << ", " << p.second << ")\n";
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) //vector
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &d) //deque
{
    os << "[";
    for (int i = 0; i < d.size(); ++i)
    {
        if (i)
            os << ", ";
        os << d[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &v) //set
{
    os << "[";
    for (auto x = v.begin(); x != v.end(); x++)
    {
        if (x != v.begin())
            os << ", ";
        os << *x;
    }
    return os << "]\n";
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const map<T1, T2> &v) //map
{
    os << " {";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << "(" << it->first << " -> " << it->second << ")"; //键值对
    }
    return os << "}\n";
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
constexpr int MOD = 998244353, INF = 1e9;
struct Fenwick
{
    int n;
    vector<i64> tr;
    Fenwick(int n_) : n(n_), tr(n + 1, 0) {}
    void add(int x, int v)
    {
        for (; x <= n; x += x & (-x))
            tr[x] += v;
    }
    i64 query(int x)
    {
        i64 res = 0;
        for (; x > 0; x -= x & (-x))
            res += tr[x];
        return res;
    }
};

struct Element
{
    int a, b, c;
    int cnt;
    int ans;

    bool operator==(const Element &o) const
    {
        return a == o.a && b == o.b && c == o.c;
    }
};

struct CDQ
{
    int n, k;
    vector<Element> p;
    Fenwick bit;

    CDQ(int n_, int k_) : n(n_), k(k_), bit(k_) {}

    void addElement(int a, int b, int c)
    {
        p.push_back({a, b, c, 1, 0});
    }

    void cdq(int l, int r)
    {
        if (l >= r)    
            return;
        int m = l + r >> 1;
        cdq(l, m);
        cdq(m + 1, r);
        auto cmpb = [](const Element &x, const Element &y) -> bool
        {
            if(x.b != y.b)
                return x.b < y.b;
            else
                return x.c < y.c;
        };
        sort(p.begin() + l, p.begin() + m + 1, cmpb);
        sort(p.begin() + m + 1, p.begin() + r + 1, cmpb);

        int i = l, j = m + 1;

        while(j <= r)
        {
            while(i <= m && p[i].b <= p[j].b)
            {
                bit.add(p[i].c, p[i].cnt);
                i++;
            }

            p[j].ans += bit.query(p[j].c);
            j++;
        }

        for (int pt = l; pt < i;pt++)
            bit.add(p[pt].c, -p[pt].cnt);
    }

    vector<i64> run()
    {
        auto cmpa = [](const Element &x, const Element &y) -> bool
        {
            if(x.a != y.a)
                return x.a < y.a;
            else if(x.b != y.b)
                return x.b < y.b;
            else
                return x.c < y.c;
        };
        sort(p.begin(), p.end(), cmpa);

        vector<Element> uniq;
        for (int i = 0; i < p.size(); i++)
        {
            if(i > 0 && p[i] == p[i - 1])
                uniq.back().cnt++;
            else
                uniq.push_back(p[i]);
        }
        p = uniq;

        for(auto &e : p)
            e.ans = e.cnt - 1;

        if(!p.empty())
            cdq(0, p.size() - 1);

        vector<i64> res(n, 0);
        for(const auto &e : p)
            res[e.ans] += e.cnt;
        return res;
    }
};
void solve()
{
    int n, k;
    cin >> n >> k;
    CDQ cd(n, k);
    for (int i = 0; i< n;i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        cd.addElement(a, b, c);
    }

    vector<i64> ans = cd.run();
    for(int k : ans)
        cout << k << "\n";
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