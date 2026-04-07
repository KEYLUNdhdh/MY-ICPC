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

//对于每个k，研究区间0 ~ k与k + 1 ~ n - 1，发现在一次双向冒泡排序后，区间0 ~ k中理应在k + 1 ~ n -  1区间的元素一定有一个且只有一个最大的会被移到右边，同理右边的也会有一个元素移到左边，只看左边区间我们的错位元素-1，那我们只要找一个区间有最多的错位元素就行（构造思想,我们去遍历每一个k
void solve()
{
    int n;
    cin >> n;
    vector<pii> a(n);
    for (int i = 0; i < n;i++)
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    vector<pii> uni = a;
    sort(uni.begin(), uni.end());
    for (int i = 0; i < n;i++)
    {
        a[uni[i].second].first = i;
    }
    // debug(a);
    int cnt = 0;
    int ans = -1;
    vector<int> vis(n, 0);
    for (int i = 0; i < n;i++)
    {
        if(i < a[i].first)
            cnt++;
        if(vis[i])
            cnt--;
        vis[a[i].first] = 1;
        chmax(ans, cnt);
    }
    cout << max(1, ans);
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