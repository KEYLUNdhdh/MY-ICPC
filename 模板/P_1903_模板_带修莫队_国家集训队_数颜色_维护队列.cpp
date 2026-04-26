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
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct MoUpdate
{
    struct Query
    {
        int l, r, t, id;
    };

    struct Update
    {
        int pos, val;
    };

    int n, blockSize;
    vector<int> a;
    vector<Query> queries;
    vector<Update> updates;
    vector<int> ans;

    vector<int> cnt;
    int cur_ans;

    MoUpdate(int n_, const vector<int> &a_, int max_val)
    {
        n = n_;
        a = a_;
        blockSize = max(1, (int)pow(n, 2. / 3.));
        cnt.assign(max_val + 1, 0);
        cur_ans = 0;
        updates.push_back({0, 0});
    }
    // ==================================================
    void addQuery(int l, int r, int t, int id)
    {
        queries.push_back({l, r, t, id});
    }

    void addUpdate(int pos, int val)
    {
        updates.push_back({pos, val});
    }

    inline void add(int idx)
    {
        int x = a[idx];
        if(cnt[x] == 0)
            cur_ans++;
        cnt[x]++;
    }

    inline void del(int idx)
    {
        int x = a[idx];
        cnt[x]--;
        if(cnt[x] == 0)
            cur_ans--;
    }

    inline void applyUpdate(int t, int L, int R)
    {
        int p = updates[t].pos;
        if(p >= L && p <= R)
        {
            del(p);
            swap(a[p], updates[t].val);
            add(p);
        }
        else
        {
            swap(a[p], updates[t].val);
        }
    }
    // =========================================

    vector<int> run()
    {
        sort(queries.begin(), queries.end(), [&](const Query &q1, const Query &q2)
        {
            int b1 = q1.l / blockSize;
            int b2 = q2.l / blockSize;
            if(b1 != b2)
                return b1 < b2;
            int r1 = q1.r / blockSize;
            int r2 = q2.r / blockSize;
            if(r1 != r2)
                return r1 < r2;

            return (r1 & 1) ? q1.t < q2.t : q1.t > q2.t;
        });

        ans.assign(queries.size(), 0);
        int L = 1, R = 0, T = 0;
        for(const auto &q : queries)
        {
            while(L > q.l)
                add(--L);
            while(R < q.r)
                add(++R);
            while(L < q.l)
                del(L++);
            while(R > q.r)
                del(R--);

            while(T < q.t)
                applyUpdate(++T, L, R);
            while(T > q.t)
                applyUpdate(T--, L, R);

            ans[q.id] = cur_ans;
        }
        return ans;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    MoUpdate mo(n, a, 1e6);
    int qid = 0, tid = 0;
    for (int i = 0; i < m;i++)
    {
        char op;
        cin >> op;
        if(op == 'Q')
        {
            int l, r;
            cin >> l >> r;
            mo.addQuery(l, r, tid, qid++);
        }
        else
        {
            int p, c;
            cin >> p >> c;
            mo.addUpdate(p, c);
            tid++;
        }
    }

    vector<int> res = mo.run();
    for (int i = 0; i < qid;i++)
        cout << res[i] << "\n";
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