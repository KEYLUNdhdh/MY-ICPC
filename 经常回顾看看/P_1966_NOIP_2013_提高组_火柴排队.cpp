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
constexpr i64 MOD = 1e8 - 3, INF = 1e9;
i64 cnt = 0;
//若想使min(Σ[(ai-bi)^2])最小，而和式中ai^2+bi^2是个定值，那么，就只能让 2*aibi 尽可能大，那我们就升序排列，次数就是逆序对的个数（结论）,不过这里探究的是数组a和b对齐的花费次数，我们进一步离散化和处理索引就能得到答案
void mergeSort(vector<i64> &a, int l, int r, vector<i64> &tmp)
{
    if(l >= r)
        return;
    int mid = l + r >> 1;
    mergeSort(a, l, mid, tmp);
    mergeSort(a, mid + 1, r, tmp);
    int i = l, j = mid + 1;
    int idx = 0;
    while(i <= mid && j <= r)
    {
        if(a[i] > a[j])
        {
            tmp[idx++] = a[j++];
            cnt = (cnt + mid - i + 1) % MOD;
        }
        else
            tmp[idx++] = a[i++];
    }
    while(i <= mid)
        tmp[idx++] = a[i++];
    while(j <= r)
        tmp[idx++] = a[j++];
    for (int k = 0; k < idx;k++)
        a[l + k] = tmp[k];
}

void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n), b(n);
    vector<i64> unia(n), unib(n);
    unordered_map<int, int> mpa, mpb;
    vector<i64> tmp(n + 5);
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        unia[i] = a[i];
    }
    for (int i = 0; i < n;i++)
    {
        cin >> b[i];
        unib[i] = b[i];
    }
    sort(unia.begin(), unia.end());
    sort(unib.begin(), unib.end());
    a.erase(unique(unia.begin(), unia.end()), unia.end());
    b.erase(unique(unib.begin(), unib.end()), unib.end());
    for (int i = 0; i < a.size();i++)
        mpa[unia[i]] = i + 1;
    for (int i = 0; i < b.size();i++)
    {
        mpb[unib[i]] = i + 1;
    }
    for (int i = 0; i < n;i++)
    {
        a[i] = mpa[a[i]];
        b[i] = mpb[b[i]];
    }
    mpb.clear();
    for (int i = 0; i < b.size();i++)
    {
        mpb[b[i]] = i + 1;
    }
    for (int i = 0; i < a.size();i++)
    {
        a[i] = mpb[a[i]];
    }
    mergeSort(a, 0, n - 1, tmp);
    // debugarr(a);
    cout << cnt;
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