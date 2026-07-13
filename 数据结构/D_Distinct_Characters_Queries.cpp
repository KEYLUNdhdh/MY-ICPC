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

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

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
    string s;
    cin >> s;
    int n = s.size();
    s = "*" + s;

    vector<Fenwick<i64>> bit(26, Fenwick<i64>(n));
    for (int i = 1; i <= n;i++)
    {
        int idx = s[i] - 'a';
        bit[idx].rangeAdd(i, i, 1);
    }
    int q;
    cin >> q;
    while(q--)
    {
        int op;
        cin >> op;
        if(op == 2)
        {
            int cnt = 0;
            int l, r;
            cin >> l >> r;
            for (int i = 0; i < 26;i++)
            {
                if(bit[i].rangeSum(l, r) >= 1)
                    cnt++;
            }

            cout << cnt << "\n";
        }
        else
        {
            int pos;
            char c;
            cin >> pos >> c;

            char ori = s[pos];
            bit[ori - 'a'].rangeAdd(pos, pos, -1);
            bit[c - 'a'].rangeAdd(pos, pos, 1);
            s[pos] = c;
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