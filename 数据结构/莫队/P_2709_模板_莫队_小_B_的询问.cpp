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
struct Mo
{
    struct Query
    {
        int l, r, id;
    };

    int n, m, blockSize;
    vector<int> a;
    vector<Query> queries;
    vector<i64> ans;

    // ===== 以下为题目特定状态，换题时根据需要修改 =====
    vector<int> cnt;
    i64 cur_ans;

    Mo (int n_, int m_, const vector<int> &a_, int max_val)
    {
        n = n_;
        m = m_;
        a = a_;
        blockSize = max(1, (int)(n / sqrt(m)));
        ans.assign(m, 0);
        cnt.assign(max_val + 1, 0);
        cur_ans = 0;
    }
    // ==================================================
    void addQuery(int l, int r, int id)
    {
        queries.push_back({l, r, id});
    }
    // ===== 核心转移逻辑：换题时只需修改这两个函数 =====
    inline void add(int idx)
    {
        int x = a[idx];
        cur_ans += 2ll * cnt[x] + 1;
        cnt[x]++;
    }

    inline void del(int idx)
    {
        int x = a[idx];
        cur_ans -= 2ll * cnt[x] - 1;
        cnt[x]--;
    }
    // ==================================================

    vector<i64> run()
    {
        sort(queries.begin(), queries.end(), [&](const Query &q1, const Query &q2)
        { 
            int b1 = q1.l / blockSize;
            int b2 = q2.l / blockSize;
            if(b1 != b2)
                return b1 < b2;
            return (b1 & 1) ? q1.r < q2.r : q2.r < q1.r; 
        });

        int L = 1, R = 0;
        for(const auto& q : queries)
        {
            while(L > q.l)
                add(--L);
            while(R < q.r)
                add(++R);
            while(L < q.l)
                del(L++);
            while(R > q.r)
                del(R--);
            ans[q.id] = cur_ans;
        }

        return ans;
    }
};
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    Mo mo(n, m, a, k);
    for (int i = 0; i < m;i++)
    {
        int l, r;
        cin >> l >> r;
        mo.addQuery(l, r, i);
    }
    vector<i64> res = mo.run();
    for(i64 k : res)
        cout << k << "\n";
    
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