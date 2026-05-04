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
    int n, q;
    cin >> n >> q;
    i64 sum = 0;
    Fenwick<i64> pre(n);
    vector<int> a(n + 1, 0);
    set<int> st;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        sum += a[i];
        pre.rangeAdd(i, i, a[i]);
        if(a[i] == 1)
            st.insert(i);
    }
    while(q--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int s;
            cin >> s;
            if((s % 2) == sum % 2 && sum >= s)
                cout << "YES\n";
            else
            {
                if(st.empty())
                {
                    cout << "NO\n";
                }
                else
                {
                    int lmst = *st.begin();
                    int rmst = *st.rbegin();
                    i64 tmp1 = pre.rangeSum(lmst + 1, n);
                    i64 tmp2 = pre.rangeSum(1, rmst - 1);
                    debug(s) debug(tmp1) debug(tmp2)
                    if(tmp1 >= s || tmp2 >= s)
                        cout << "YES\n";
                    else
                        cout << "NO\n";
                }
            }
        }
        else
        {
            int i, v;
            cin >> i >> v;
            sum = sum - a[i] + v;
            pre.rangeAdd(i, i, -a[i]);
            a[i] = v;
            pre.rangeAdd(i, i, a[i]);
            if(v == 1)
                st.insert(i);
            else
                st.erase(i);
        }
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