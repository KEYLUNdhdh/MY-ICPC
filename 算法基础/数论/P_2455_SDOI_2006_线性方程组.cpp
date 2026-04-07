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
struct Gauss
{
    static constexpr db EPS = 1e-8;
    //a n * (n + 1)
    static int solve(vector<vector<db>> &a,vector<db> &res)
    {
        int n = a.size();
        int r = 0;
        for (int i = 0; i < n;i++)
        {
            int maxrow = r;
            for (int j = r + 1; j < n;j++)
            {
                if(abs(a[j][i]) > abs(a[maxrow][i]))
                    maxrow = j;
            }
            if(abs(a[maxrow][i]) < EPS)
                continue;

            swap(a[r], a[maxrow]);
            db pivot = a[r][i];
            for (int j = i; j <= n;j++)
                a[r][j] /= pivot;
            for (int j = 0; j < n;j++)
            {
                if(r != j)
                {
                    db factor = a[j][i];
                    for (int k = i; k <= n;k++)
                        a[j][k] -= factor * a[r][k];
                }
            }
            r++;
        }
        if(r < n)
        {
            for (int i = r; i < n;i++)
            {
                if(abs(a[i][n]) > EPS)
                    return -1;
            }
            return 0;
        }
        res.resize(n);
        for (int i = 0; i < n;i++)
            res[i] = a[i][n];
        return 1;
    }
};


void solve()
{
    int n;
    cin >> n;
    vector<vector<db>> a(n, vector<db>(n + 1, 0));
    for (int i = 0; i < n;i++)
        for (int j = 0; j <= n;j++)
            cin >> a[i][j];
    vector<db> res;
    int f = Gauss::solve(a, res);
    if(f != 1)
        cout << f;
    else
    {
        for (int i = 0; i < n;i++)
        {
            cout << "x" << i + 1 << "=";
            cout << fixed << setprecision(2) << res[i] << "\n";
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