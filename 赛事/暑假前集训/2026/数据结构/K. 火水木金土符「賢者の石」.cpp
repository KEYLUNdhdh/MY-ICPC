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
constexpr int MOD = 1e9 + 7, INF = 1e9;

i64 qpow(i64 a, i64 b) {
    i64 res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}


struct Mo
{
    struct Query
    {
        int l, r, id, totalid;
    };

    int n, m, blockSize, k;
    vector<int> a;
    vector<Query> queries;
    vector<pll> ans;
    // ===== 以下为题目特定状态，换题时根据需要修改 =====
    vector<int> cnt;
    i64 cur_ans;

    void init(int n_, int m_, const vector<int> &a_, int max_val)
    {
        n = n_;
        m = m_;
        a = a_;
        blockSize = max(1, (int)(n / sqrt(m)));
        ans.assign(m, {0, 0});
        cnt.assign(max_val + 1, 0);
        cur_ans = 0;
    }
    // ==================================================
    void addQuery(int l, int r, int id, int totalid)
    {
        queries.push_back({l, r, id, totalid});
    }
    // ===== 核心转移逻辑：换题时只需修改这两个函数 =====
    inline void add(int idx)
    {
        int x = a[idx];
        cur_ans = (cur_ans - qpow(cnt[x], k) + MOD) % MOD;
        cnt[x]++;
        cur_ans = (cur_ans + qpow(cnt[x], k)) % MOD;

    }

    inline void del(int idx)
    {
        int x = a[idx];
        cur_ans = (cur_ans - qpow(cnt[x], k) + MOD) % MOD;
        cnt[x]--;
        cur_ans = (cur_ans + qpow(cnt[x], k)) % MOD;
    }
    // ==================================================

    vector<pll> run()
    {
        if(queries.empty())
        {
            return vector<pll>();
        }
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
            ans[q.id].first = cur_ans;
            ans[q.id].second = q.totalid;
        }

        return ans;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> idx(6, 0);
    vector<Mo> m(6);
    vector<int> a(n + 1, 0);
    vector<int> ans(q, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 0; i < q;i++)
    {
        int l, r, k;
        cin >> l >> r >> k;
        m[k].addQuery(l, r, idx[k], i);
        idx[k]++;
    }
    for (int i = 1; i <= 5; i++)
    {
        m[i].init(n, idx[i], a, 1e5 + 1);
        m[i].k = i;
        vector<pll> tmp = m[i].run();
        if(!tmp.empty())
        {
            for(auto &[res, id] : tmp)
                ans[id] = res;
        }
    }

    for (int i = 0;i < q;i++)
        cout << ans[i] << "\n";
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