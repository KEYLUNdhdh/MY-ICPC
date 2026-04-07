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
struct ant
{
    int pos;
    string name;
    int time = 0;
    int d = -1;//
};
void solve(int tt)
{
    int n, l;
    cin >> n >> l;
    deque<ant> ll, rr;
    deque<ant> all;
    deque<ant> ans;
    for (int i = 0; i < n;i++)
    {
        ant tmp;
        cin >> tmp.name >> tmp.pos;
        char d;
        cin >> d;
        if(d == 'L')
        {
            tmp.time = tmp.pos;
            tmp.d = 0;
            ll.push_back(tmp);
        }
        else
        {
            tmp.time = l - tmp.pos;
            tmp.d = 1;
            rr.push_back(tmp);
        }
        all.push_back(tmp);
    }
    sort(ll.begin(), ll.end(), [](ant p, ant q)
         { return p.time < q.time; });
    sort(rr.begin(), rr.end(), [](ant p, ant q)
         { return p.time < q.time; });
    sort(all.begin(), all.end(), [](ant p, ant q)
         { return p.pos < q.pos; });
    for (int i = 0;i < ll.size();i++)
    {
        ll[i].name = all[i].name;
        ans.push_back(ll[i]);
    }
    for (int i = 0; i < rr.size();i++)
    {
        int idx = n - 1 - i;
        rr[i].name = all[idx].name;
        ans.push_back(rr[i]);
    }
    sort(ans.begin(), ans.end(), [](ant p, ant q)
         { return p.time < q.time; });
    cout << "Case #" << tt << ":\n";
    for(auto k : ans)
        cout << k.time << " " << k.name << "\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T;i++)
    {
        solve(i);
    }
    return 0;
}