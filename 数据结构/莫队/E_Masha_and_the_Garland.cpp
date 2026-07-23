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

struct Mo
{
    struct Query
    {
        int l, r, id;
    };

    int n, m, blockSize;
    string a;
    vector<Query> queries;
    vector<pll> ans;

    // ===== 以下为题目特定状态，换题时根据需要修改 =====
    vector<int> cnt;
    i64 curans;

    Mo (int n_, int m_, const string &a_)
    {
        n = n_;
        m = m_;
        a = a_;
        blockSize = max(1, (int)(n / sqrt(m)));
        ans.assign(m, {0, -1});
        curans = 0;
    }
    // ==================================================
    void addQuery(int l, int r, int id)
    {
        queries.push_back({l, r, id});
    }
    // ===== 核心转移逻辑：换题时只需修改这两个函数 =====
    inline void add(int idx, int t)
    {
        if(t == 0)
        {
            if(a[idx] != a[idx + 1])
                curans++;
        }
        else
        {
            if(a[idx] != a[idx - 1])
                curans++;
        }
    }

    inline void del(int idx, int t)
    {
        if(t == 0)
        {
            if(a[idx] != a[idx + 1])
                curans--;
        }
        else
        {
            if(a[idx] != a[idx - 1])
                curans--;
        }
    }
    // ==================================================

    vector<pll> run()
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
                add(--L, 0);
            while(R < q.r)
                add(++R, 1);
            while(L < q.l)
                del(L++, 0);
            while(R > q.r)
                del(R--, 1);
            ans[q.id].first = curans, ans[q.id].second = a[L] - '0';
        }

        return ans;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    string x(n, '*');
    for (int i = 0; i < n;i++)
    {
        if(i & 1)
            x[i] = '0' + ((s[i] - '0') ^ 1);
        else
            x[i] = s[i];
    }
    x = "*" + x + "?";
    Mo mo(n, q, x);
    vector<int> k(q);
    for (int i = 0; i < q;i++)
    {
        int l, r;
        cin >> l >> r >> k[i];

        mo.addQuery(l, r, i);
    }

    vector<pll> ans = mo.run();
    for (int i = 0; i < q;i++)
    {
        auto &[cnt, s] = ans[i];
        if(cnt / 2 <= k[i])
            cout << "YES\n";
        else
            cout << "NO\n";
    }
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