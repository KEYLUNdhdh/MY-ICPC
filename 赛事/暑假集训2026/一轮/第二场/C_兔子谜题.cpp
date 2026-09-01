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
using u32 = unsigned int;
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

template<typename T,typename F>
struct STable
{
    int n;
    int maxlog;
    vector<vector<T>> st;
    F func;
    //a 1 - index
    STable(const vector<T>& a,const F& f) : func(f)
    {
        n = a.size() - 1;
        maxlog = __lg(n) + 1;
        st.assign(n + 1, vector<T>(maxlog));
        for (int i = 1; i <= n;i++)
            st[i][0] = a[i];
        for (int j = 1; j < maxlog;j++)
        {
            int len = 1 << (j - 1);
            for (int i = 1;i <= n - (1 << j) + 1;i++)
                st[i][j] = func(st[i][j - 1], st[i + len][j - 1]);
        }
    }
    inline T query(int l,int r) const
    {
        if (l > r) 
            swap(l, r);
        int k = __lg(r - l + 1);
        return func(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n + 1, 0);
    vector<i64> premax(n + 1, 0), sufmin(n + 1, 0);
    vector<i64> ans(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        premax[i] = max(premax[i - 1], a[i]);
    }
    
    STable st(a, [](i64 a, i64 b) { return max(a, b); });
    sufmin[n] = a[n];
    for (int i = n - 1; i >= 1;i--)
        sufmin[i] = min(sufmin[i + 1], a[i]);

    vector<int> pos;
    for (int i = 1; i <= n - 1;i++)
    {
        if(premax[i] > sufmin[i + 1])
            continue;
        else
            pos.push_back(i);
    }
    // debugarr(premax)
    // debugarr(sufmin)
    // debugarr(pos) cutline
    int l = 1;
    for (int i = 0; i < pos.size();i++)
    {
        int lim = pos[i];
        i64 maxx= st.query(l, lim);
        for (int k = l; k <= lim;k++)
            cout << maxx << " ";
        l = lim + 1;
    }

    i64 maxx = st.query(l, n);
    for (int i = l; i <= n;i++)
        cout << maxx << " ";
    cout << "\n";
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