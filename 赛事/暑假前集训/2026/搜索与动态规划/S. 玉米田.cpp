#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

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
constexpr i64 MOD = 998244353, INF = 1e9;

template<typename T>
struct FenwickMax 
{
    int n, m;
    vector<T> tr;

    FenwickMax(int n_ = 0, int m_ = 0) 
    {
        init(n_, m_);
    }

    void init(int n_ = 0, int m_ = 0) 
    {
        n = n_;
        m = m_;
        tr.assign((n + 1) * (m + 1), 0); 
    }

    inline int id(int x, int y) const 
    {
        return x * (m + 1) + y;
    }

    void update(int x, int y, T v) 
    {
        for (int i = x; i <= n; i += i & (-i)) 
        {
            for (int j = y; j <= m; j += j & (-j)) 
            {
                int pos = id(i, j);
                chmax(tr[pos], v);
            }
        }
    }

    T query(int x, int y) 
    {
        T ans{}; 
        for (int i = x; i > 0; i -= i & (-i)) 
        {
            for (int j = y; j > 0; j -= j & (-j)) 
            {
                int pos = id(i, j);
                chmax(ans, tr[pos]);
            }
        }
        return ans;
    }
};

void solve()
{
    int n, k;   
    cin >> n >> k;

    vector<int> a(n + 1, 0);
    int maxx = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        chmax(maxx, a[i]);
    }

    FenwickMax<int> fw(maxx + k + 1, k + 2);
    int ans = 0;

    for (int i = 1; i <= n;i++)
    {
        for (int j = k; j >= 0;j--)
        {
            int val = a[i] + j;
            int cnt = j + 1;

            int len = fw.query(val, cnt) + 1;
            chmax(ans, len);

            fw.update(val, cnt, len);
        }
    }

    cout << ans;
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