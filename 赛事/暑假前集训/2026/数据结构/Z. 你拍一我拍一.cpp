#include <bits/stdc++.h>
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
constexpr i64 MOD = 998244353, INF = 1e18;

template<class T>
T ceilDiv(T n, T m) {
    if (n >= 0) {
        return (n + m - 1) / m;
    //-
    } else {
        return n / m;
    }
}

struct RollbackMo
{
    struct Query
    {
        int l, r, id;
    };

    int n, m, blockSize;
    vector<i64> b, s;
    vector<Query> queries;  
    vector<i64> ans;

    vector<i64> maxb;
    i64 summaxb;

    RollbackMo(int n_, int m_, const vector<i64> &b_,const vector<i64> s_, int maxval)
    {
        n = n_;
        m = m_;
        b = b_;
        s = s_;
        blockSize = max(1, (int)(n / sqrt(m)));

        maxb.assign(maxval, -INF);
        summaxb = 0;
    }

    void addQuery(int l, int r, int id)
    {
        queries.push_back({l, r, id});
    }

    i64 bruteForce(int l, int r)
    {
        vector<pll> his;
        i64 tmp = summaxb;
        for (int i = l; i <= r;i++)
        {
            int c = i % m;
            if(b[i] > maxb[c])
            {
                his.push_back({c, maxb[c]});
                if(maxb[c] != -INF)
                    tmp -= maxb[c];
                maxb[c] = b[i];
                tmp += maxb[c];
            }
        }
        i64 res = ceilDiv(s[1] + tmp, (i64)m);
        for (int i = his.size() - 1; i >= 0;i--)
        {
            int c = his[i].first;
            maxb[c] = his[i].second;
        }

        return res;
    }

    vector<i64> run()
    {
        sort(queries.begin(), queries.end(), [&](const Query &q1, const Query &q2)
        {
            int b1 = q1.l / blockSize;
            int b2 = q2.l / blockSize;
            if(b1 != b2)
                return b1 < b2;
            return q1.r < q2.r;
        });

        int lastblock = -1;
        int L = 1, R = 0;

        vector<pll> his;
        ans.assign(queries.size(), 0);
        for(const auto &q : queries)
        {
            if(q.r - q.l + 1 < m)
            {
                ans[q.id] = -INF;
                continue;
            }

            int curblock = q.l / blockSize;
            if(curblock != lastblock)
            {
                lastblock = curblock;
                summaxb = 0;
                maxb.assign(m, -INF);
                R = min(n, (curblock + 1) * blockSize - 1);
                L = R + 1;
            }
            
            if(curblock == q.r / blockSize)
            {
                ans[q.id] = bruteForce(q.l, q.r);
                continue;
            }

            while(R < q.r)
            {
                R++;
                int c = R % m;
                if(b[R] > maxb[c])
                {
                    if(maxb[c] != -INF)
                        summaxb -= maxb[c];
                    maxb[c] = b[R];
                    summaxb += maxb[c];
                }
            }

            int tmpL = L;
            his.clear();
            while(tmpL > q.l)
            {
                tmpL--;
                int c = tmpL % m;
                if(b[tmpL] > maxb[c])
                {
                    his.push_back({c, maxb[c]});
                    if(maxb[c] != -INF)
                        summaxb -= maxb[c]; 
                    maxb[c] = b[tmpL];
                    summaxb += maxb[c];
                }
            }

            ans[q.id] = ceilDiv(s[1] + summaxb, (i64)m);

            for (int i = his.size() - 1; i >= 0;i--)
            {
                int c = his[i].first;

                summaxb -= maxb[c];
                maxb[c] = his[i].second;
                if(maxb[c] != -INF)
                    summaxb += maxb[c];
            }
        }

        return ans;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> s(n - m + 2, 0);
    vector<i64> b(n + 1, 0);
    for (int i = 1; i <= n - m + 1;i++)
        cin >> s[i];
    for (int i = m + 1; i <= n;i++)
        b[i] = s[i - m + 1] - s[i - m] + b[i - m];
    RollbackMo mo(n, m, b, s, m);

    int q;
    cin >> q;
    for (int i = 0; i < q;i++)
    {
        int l, r;
        cin >> l >> r;
        mo.addQuery(l, r, i);
    }

    vector<i64> ans = mo.run(); 
    for (i64 k : ans)
    {
        if(k == -INF)
            cout << "unbounded\n";
        else
            cout << k << "\n";
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