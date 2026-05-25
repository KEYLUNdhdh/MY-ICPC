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
    vector<i64> w(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> w[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(n + 1, 0);
    vector<int> incyc(n + 1, 0);
    vector<int> pa(n + 1, 0);
    vector<int> cycle;
    int f = 0;

    auto dfs = [&](auto self, int u, int p) -> void
    {
        if(f)
            return;

        vis[u] = 1;
        pa[u] = p;
        for (int v : adj[u])
        {
            if(f)
                return;
            if(v == p)
                continue;
            
            if(vis[v] == 1)
            {
                int cur = u;
                while(cur != v)
                {
                    cycle.push_back(cur);
                    incyc[cur] = 1;
                    cur = pa[cur];
                }
                cycle.push_back(cur);
                incyc[cur] = 1;
                f = 1;
            }
            else
                self(self,v , u);
        }
    };

    dfs(dfs, 1, 0);

    i64 ans = 0;
    vector<i64> subMax1(n + 1, 0), subMax2(n + 1, 0);
    auto dfsSub = [&](auto self, int u, int p) -> void
    {
        i64 m1 = 0, m2 = 0;
        for(int v : adj[u])
        {
            if(v == p || incyc[v])
                continue;
            self(self, v, u);
            i64 maxx = subMax1[v];
            if(maxx > m1)
            {
                m2 = m1;
                m1 = maxx;
            }
            else if(maxx > m2)
                m2 = maxx;
        }
        subMax1[u] = w[u] + m1;
        subMax2[u] = w[u] + m2;
        chmax(ans, w[u] + m1 + m2);
    };

    i64 sumcycle = 0;
    for (int u : cycle)
        sumcycle += w[u];

    for (int i = 0; i < cycle.size(); i++)
    {
        int c = cycle[i];
        dfsSub(dfsSub, c, 0);
        chmax(ans, subMax1[c] + subMax2[c] + sumcycle - 2ll * w[c]);
    }

    vector<i64> prefix = {0};
    int k = cycle.size();
    for (int i = 0; i < 2 * k;i++)
        prefix.push_back(w[cycle[i % k]]);
    for (int i = 1; i <= 2 * k;i++)
        prefix[i] = prefix[i - 1] + prefix[i];

    vector<i64> starr(2 * k + 1, 0);
    for (int i = 1; i <= 2 * k;i++)
    {
        int c = cycle[(i - 1) % k];
        i64 d = subMax1[c] - w[c];
        i64 pre = prefix[i - 1];
        starr[i] = d - pre;
    }

    STable st(starr, [](i64 a, i64 b)
              { return max(a, b); });

    for (int j = 2; j <= 2 * k;j++)
    {
        int c = cycle[(j - 1) % k];
        i64 cur = subMax1[c] - w[c] + prefix[j];
        i64 l = max(1, j - k + 1);
        i64 r = max(1, j - 1);
        i64 add = st.query(l, r);
        chmax(ans, cur + add);
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