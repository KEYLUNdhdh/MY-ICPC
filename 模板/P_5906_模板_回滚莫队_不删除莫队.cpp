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

struct RollbackMo
{
    struct Query
    {
        int l, r, id;
    };

    int n, m, blockSize;
    vector<int> a;
    vector<Query> queries;  
    vector<int> ans;

    vector<int> firstpos, lastpos;
    int curans;

    RollbackMo(int n_, int m_, const vector<int> &a_, int maxval)
    {
        n = n_;
        m = m_;
        a = a_;
        blockSize = max(1, (int)(n / sqrt(m)));
        ans.assign(m, 0);

        firstpos.assign(maxval + 1, 0);
        lastpos.assign(maxval + 1, 0);
    }

    void addQuery(int l, int r, int id)
    {
        queries.push_back({l, r, id});
    }

    int bruteForce(int l, int r)
    {
        int res = 0;
        for (int i = l; i <= r;i++)
        {
            if(!firstpos[a[i]])
                firstpos[a[i]] = i;
            res = max(res, i - firstpos[a[i]]);
        }
        for (int i = l; i <= r;i++)
        {
            firstpos[a[i]] = 0;
        }
        return res;
    }

    vector<int> run()
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

        for(const auto &q : queries)
        {
            int curblock = q.l / blockSize;
            
            if(curblock != lastblock)
            {
                for (int i = R; i >= L;i--)
                {
                    firstpos[a[i]] = 0;
                    lastpos[a[i]] = 0;
                }

                L = (curblock + 1) * blockSize;
                R = L - 1;
                curans = 0;
                lastblock = curblock;
            }

            if(curblock == q.r / blockSize)
            {
                ans[q.id] = bruteForce(q.l, q.r);
                continue;
            }


            while(R < q.r)
            {
                R++;
                if(!firstpos[a[R]])
                    firstpos[a[R]] = R;
                lastpos[a[R]] = R;
                curans = max(curans, R - firstpos[a[R]]);
            }

            int tmpL = L;
            int tmpans = curans;

            while(tmpL > q.l)
            {
                tmpL--;
                int x = a[tmpL];
                if(!lastpos[x])
                    lastpos[x] = tmpL;
                tmpans = max(tmpans, lastpos[x] - tmpL);
            }

            ans[q.id] = tmpans;

            for (int i = q.l; i < L;i++)
            {
                int x = a[i];
                if(lastpos[x] == i)
                    lastpos[x] = 0;
            }
        }

        return ans;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, -1);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    vector<int> uni = a;
    sort(uni.begin(), uni.end());
    uni.erase(unique(uni.begin(), uni.end()), uni.end());
    for (int i = 1; i <= n;i++)
    {
        int mp = lower_bound(uni.begin(), uni.end(), a[i]) - uni.begin();
        a[i] = mp;
    }
    debugarr(a)
    int m;
    cin >> m;
    RollbackMo mo(n, m, a, n + 1);
    for (int i = 0; i < m;i++)
    {
        int l, r;
        cin >> l >> r;
        mo.addQuery(l, r, i);
    }

    vector<int> res = mo.run();
    for (int k : res)
        cout << k << "\n";
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