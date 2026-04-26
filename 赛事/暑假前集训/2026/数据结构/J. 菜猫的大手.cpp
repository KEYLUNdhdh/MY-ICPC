#include <bits/stdc++.h>
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
constexpr int MOD = 998244353, INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    for (int i = 1; i <= n;i++)
        cin >> b[i];

    vector<int> l(n + 1, 0), r(n + 1, n + 1);
    deque<int> d;
    for (int i = 1; i <= n;i++)
    {
        while(!d.empty() && a[d.back()] >= a[i])
            d.pop_back();
        if(!d.empty())
            l[i] = d.back();
        d.push_back(i);
    }
    d.clear();
    for (int i = n; i >= 1;i--)
    {
        while(!d.empty() && a[d.back()] >= a[i])
            d.pop_back();
        if(!d.empty())
            r[i] = d.back();
        d.push_back(i);
    }
    // debugarr(l)
    // debugarr(r)

    vector<int> minmax(n + 1, 0);
    for(int i = 1;i <= n;i++)
    {
        int ll = l[i], rr = r[i];
        int len = rr - ll - 1;
        int minn = a[i];
        chmax(minmax[len], minn);
    }
    for (int i = n; i >= 1;i--)
    {
        chmax(minmax[i - 1], minmax[i]);
    }

    for (int i = 1; i <= n;i++)
    {
        int len = i;
        int lw = b[i];
        if(minmax[len] >= lw)
            cout << 1;
        else
            cout << 0;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}