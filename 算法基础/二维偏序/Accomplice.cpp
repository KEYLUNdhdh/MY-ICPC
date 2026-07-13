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

template<typename T>
struct Fenwick
{
    int n;
    vector<T> t1, t2;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        t1.assign(n + 1, T{});
        t2.assign(n + 1, T{});
    }

    void add(int x,T v)
    {
        T v2 = v * x;
        for (int i = x; i <= n;i += i & (-i))
        {
            t1[i] += v;
            t2[i] += v2;
        }
    }

    void rangeAdd(int l, int r, T v)
    {
        add(l, v);
        add(r + 1, -v);
    }

    T sum(int x)
    {
        T sum1{}, sum2{};
        for (int i = x; i > 0;i -= i & (-i))
        {
            sum1 += t1[i];
            sum2 += t2[i];
        }
        return sum1 * (x + 1) - sum2;
    }

    T rangeSum(int l,int r)
    {
        return sum(r) - sum(l - 1);
    }
    
};

void solve()
{
    i64 n, d;
    cin >> n >> d;

    vector<i64> vals;
    vector<pll> inter;
    for (int i = 0; i < n;i++)
    {
        i64 l, r;
        cin >> l >> r;
        i64 ava = r - d;
        if(l <= ava)
        {
            inter.push_back({l, ava});
            vals.push_back(l);
            vals.push_back(ava);
        }
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    int len = vals.size();
    Fenwick<i64> sum(len + 1);
    Fenwick<i64> cnt(len + 1);

    i64 ans = 0;
    auto get = [&](i64 x) -> int
    {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    };

    sort(inter.begin(), inter.end());
    for(auto &[l, r] : inter)
    {
        int rkr = get(r);
        int rkl = get(l);

        i64 cnt1 = cnt.rangeSum(rkl, rkr);
        i64 sum1 = sum.rangeSum(rkl, rkr);
        ans += sum1 - cnt1 * (l - 1);

        i64 cnt2 = cnt.rangeSum(rkr + 1, len);
        ans += cnt2 * (r - l + 1);

        cnt.rangeAdd(rkr, rkr, 1);
        sum.rangeAdd(rkr, rkr, r);
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