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
const int P = 998244353;
struct SegmentTree {
    int n;
    vector<int> tag;
    vector<bitset<32>> all;
    SegmentTree(int n_) : n(n_), tag(4 * n + 1, 0), all(4 * n + 1)
    {
        init(1, 1, n);
    }

    void init(int p, int l, int r)
    {
        if(l == r)
        {
            all[p][1] = 1;
            return;
        }
        int m = l + r >> 1;
        init(p << 1, l, m);
        init(p << 1 | 1, m + 1, r);
        pull(p);
        return;
    }

    void pull(int p)
    {
        all[p] = all[p << 1] | all[p << 1 | 1];
    }

    void push(int p)
    {
        if(tag[p])
        {
            all[p << 1] = all[p];
            all[p << 1 | 1] = all[p];
            tag[p << 1] = tag[p];
            tag[p << 1 | 1] = tag[p];
            tag[p] = 0;
        }
    }
    
    void query(int p, int l, int r, int x, int y, bitset<32> &ans) 
    {
        if (l > y || r < x) 
        {
            return;
        }
        if (l >= x && r <= y) 
        {
            ans |= all[p];
            return;
        }
        int m = (l + r) / 2;
        push(p);
        query(2 * p, l, m, x, y, ans);
        query(2 * p + 1, m + 1, r, x, y, ans);
        return;
    }
    
    int query(int x, int y) 
    {
        bitset<32> tmp;
        query(1, 1, n, x, y, tmp);
        return tmp.count();
    }
    
    void modify(int p, int l, int r, int x, int y, int v) 
    {
        if(l > y|| r < x)
            return;
        if(l >= x && r <= y)
        {
            tag[p] = v;
            all[p] &= 0;
            all[p][v] = 1;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        modify(p << 1, l, m, x, y, v);
        modify(p << 1 | 1, m + 1, r, x, y, v);
        pull(p);
    }
    
    void modify(int x, int y, int v) 
    {
        modify(1, 1, n, x, y, v);
    }
};
void solve()
{
    int l, t, o;
    cin >> l >> t >> o;
    SegmentTree sg(l);
    while(o--)
    {
        char op;
        cin >> op;
        if(op == 'C')
        {
            int a, b, c;
            cin >> a >> b >> c;
            if(a > b)
                swap(a, b);
            sg.modify(a, b, c);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            if(a > b)
                swap(a, b);
            cout << sg.query(a, b) << "\n";
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