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
struct seg
{
    int l, r;
    bool operator<(const seg &b) const
    {
        int len1 = r - l + 1;
        int len2 = b.r - b.l + 1;
        if(len1 != len2)
            return len1 < len2;
        else
            return l > b.l;
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<seg> d;
    vector<int> ans(n + 1, 0);
    seg init = {1, n};
    priority_queue<seg, vector<seg>> pq;
    pq.push(init);
    int tot = 1;
    while(!pq.empty())
    {
        seg tmp = pq.top();
        pq.pop();
        if(tmp.r == tmp.l)
        {
            ans[tmp.l] = tot++;
            continue;
        }
        else if(tmp.l + 1 == tmp.r)
        {
            ans[tmp.l] = tot++;
            seg a = {tmp.r, tmp.r};
            pq.push(a);
            continue;
        }
        int len = tmp.r - tmp.l + 1;
        int pos = (len + 1) / 2 - 1 + tmp.l;
        ans[pos] = tot++;
        seg a, b;
        a = {tmp.l, pos - 1};
        b = {pos + 1, tmp.r};
        pq.push(a);
        pq.push(b);
    }
    for (int i = 1; i <= n;i++)
        cout << ans[i] << " ";
    cout << "\n";
    // cutline
}

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