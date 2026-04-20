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

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    vector<int> ans(n + 1, -1);
    vector<int> wa;
    map<int, int> mp;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        mp[a[i]] = i;
        if(a[i] == i)
            ans[i] = 0;
        else
            wa.push_back(i);
    }
    int len = wa.size();
    // debugarr(wa)
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < len;i++)
    {
        int poss = wa[i];
        int num = a[wa[i]];
        int pos = lower_bound(wa.begin(), wa.end(), num) - wa.begin();
        int cnt = (pos - i + len) % len;
        ans[num] = cnt;
        pq.push({cnt, num});
    }
    int less = 0;
    int totalpace = 0;
    while(!pq.empty())
    {
        auto [cnt, num] = pq.top();
        while(!pq.empty())
        {
            auto [cntt, numm] = pq.top();
            if(cntt != cnt)
            {
                break;
            }
            else
            {
                ans[numm] = cntt - totalpace;
                less++;
                pq.pop();
            }
        }
        totalpace++;
    }
    // debugarr(ans)
    for (int i = 1; i <= n;i++)
        cout << ans[i] << " ";
}
//4 1 3 1 0 1 
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