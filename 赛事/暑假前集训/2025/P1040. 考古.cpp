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
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int P = 998244353;
struct SegmentTree
{
    int n;
    vector<int>  mo, maxx, now;
    SegmentTree(int n_) : n{n_}, mo(4 * n + 1, 0), maxx(4 * n + 1, 0), now(4 * n + 1, 0) {}
    void pull(int p)
    {
        now[p] = max(now[p << 1], now[p << 1 | 1]);
        chmax(maxx[p], now[p]);
    }
    void push(int p,int l,int r)
    {
        if(mo[p] != 0)
        {
            int m = l + (r - l) / 2;
            applyAdd(2 * p, l, m, mo[p]);
            applyAdd(2 * p + 1, m + 1, r, mo[p]);
            mo[p] = 0;
        }
    }
    
    void applyAdd(int p,int l,int r,int v)
    {
        now[p] += v;
        mo[p] += v;
        chmax(maxx[p], now[p]);
    }
    void rangeAdd(int p,int l,int r,int x,int y,int v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applyAdd(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeAdd(int x,int y,int v)
    {
        rangeAdd(1, 1, n, x, y, v);
    }
};

//我们去枚举右边界
//假设我们现在读入第 R 个元素，颜色为 C。
//我们需要知道这个颜色 C 上一次出现的位置，以及上上次出现的位置。
//用数组（或者 map）记录每个颜色上一次出现的下标，设为 last[C]，再上一次出现的下标设为 pre[C]。
//当颜色 C 第 R 次出现时，它会怎么影响不同起点 L 对应的区间 [L,R] 呢？
//左端点 L 落在 (last[C],R 之间：
//在这个区间里，颜色 C 刚好出现了第 1 次！这就意味着，以这些点为起点的区间，独一无二的颜色数多了一个。操作：线段树区间加法 update(last[C] + 1,R 1)。
//左端点 L 落在 (pre[C], last[C]] 之间：
//在这个区间里，颜色 C 已经出现了第 2 次（在 last[C] 和R各出现一次）。原本在扫描到 last[C] 时，它被算作了“只出现一次”，但现在它出现了两次，不再是独一无二的了！所以它的贡献必须被扣除。操作：线段树区间减法 update(pre[C] + 1, last[C], -1)。
//左端点 L <= pre[C]：在这个区间里，颜色 C 已经出现了 3 次甚至更多，它早就不符合“只出现一次”的条件了，因此对于这些左端点，没有新的影响，不需要更新。
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 1);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    map<int, int> l, ll;
    SegmentTree sg(n);
    i64 ans = 0;
    for (int i = 1; i <= n;i++)
    {
        int r = i;
        int pre = l[a[i]];
        int ppre = ll[a[i]];
        sg.rangeAdd(pre + 1, r, 1);
        sg.rangeAdd(ppre + 1, pre, -1);
        ll[a[i]] = l[a[i]]; 
        l[a[i]] = i;
    }
    cout << sg.maxx[1];
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