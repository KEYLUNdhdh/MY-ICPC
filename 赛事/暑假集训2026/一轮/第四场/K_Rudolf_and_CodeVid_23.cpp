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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

struct edge
{
    int l, r, w;
};

const int MAXN = 20005;

inline i64 read(int n)
{
    i64 t;
    cin >> t;
    i64 res = 0;
    for (int i = 0; i < n;i++)
    {
        if(t % 10)
            res += pow(2, i);
        t /= 10;
    }
    return res;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    i64 s;
    s = read(n);
    // debug(s)
    vector<edge> edges(m);
    for (int i = 0; i < m;i++)
    {
        // cin >> edges[i].w >> edges[i].l >> edges[i].r;
        cin >> edges[i].w;
        edges[i].l = read(n);
        // debug(edges[i].l)
        edges[i].r = read(n);
        // debug(edges[i].r)

    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, s});
    vector<i64> dist(MAXN, INF);
    // dist[s] = 0;
    // debug(s)
    i64 ans = -1;
    while(!pq.empty())
    {
        auto [d, ste] = pq.top();
        pq.pop();

        if(d >= dist[ste])
            continue;
        dist[ste] = d;

        if(ste == 0)
        {
            cout << d << "\n";
            return;
        }

        for(auto &[l, r, w] : edges)
        {
            i64 nxt = (ste & (~l)) | r;
            pq.push({w + d, nxt});
        }
    }
    // debug(s)
    cout << -1 << "\n";
    return;
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}