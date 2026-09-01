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

constexpr i64 MOD = 998244353, INF = 2e18;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pll>> adj(n + 1);
    int p, g;
    cin >> p >> g;
    for (int i = 1; i <= m;i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    vector<i64> distp(n + 1, INF), distg(n + 1, INF), distno(n + 1, INF);

    priority_queue<pll, vector<pll>, greater<pll>> pq;

    distp[p] = 0;
    pq.push({0, p});
    while(!pq.empty())
    {
        auto [dis, u] = pq.top();
        pq.pop();

        if(dis > distp[u])
            continue;

        for(auto &[w, v] : adj[u])
        {
            if(distp[u] + w < distp[v])
            {
                distp[v] = distp[u] + w;
                pq.push({distp[v], v});
            }
        }
    }

    distg[g] = 0;
    pq.push({0, g});
    while(!pq.empty())
    {
        auto [dis, u] = pq.top();
        pq.pop();

        if(dis > distg[u])
            continue;

        for(auto &[w, v] : adj[u])
        {
            if(distg[u] + w < distg[v])
            {
                distg[v] = distg[u] + w;
                pq.push({distg[v], v});
            }
        }
    }

    distno[p] = 0;
    pq.push({0, p});
    while(!pq.empty())
    {
        auto [dis, u] = pq.top();
        pq.pop();

        if(dis > distno[u] || u == g)
            continue;

        for(auto &[w, v] : adj[u])
        {
            if(distno[u] + w < distno[v] && v != g)
            {
                distno[v] = distno[u] + w;
                pq.push({distno[v], v});
            }
        }
    }

    vector<int> ans;
    for (int i = 1; i <= n;i++)
    {
        if(distp[i] % 2 == 0 && distno[i] > distp[i])
        {
            i64 len = distp[i] / 2;
            if(distp[g] == len && distg[i] == len)
                ans.push_back(i);
        }
    }
    if(ans.empty())
    {
        cout << "*";
        return;
    }
    for(int k : ans)
        cout << k << " ";
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}