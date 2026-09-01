// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
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
#define KEYLUN main
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
void debug_out() { cerr << "\n"; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) { cerr << " " << H; debug_out(T...); }
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char* names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char* names, Head H, Tail... T) {
    while (*names == ' ' || *names == ',') names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i) {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[') bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']') bracket--;
        else if (names[i] == ',' && bracket == 0) break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H) cerr << v << " ";
    cerr << "\n"; 
    
    debugarr_out(names + i + 1, T...);
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template<class T> void chmin(T &a, T b) { if (a > b) a = b; }
template<class T> void chmax(T &a, T b) { if (a < b) a = b; }
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pii>> adj(n + 1);
    vector<int> tag(m, 0);
    vector<tuple<int, int, int>> edges(m);
    map<int, map<int, int>> mp;
    for (int i = 0; i < m;i++)
    {
        int u, v, z;
        cin >> u >> v >> z;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        edges[i] = {u, v, z};
        mp[u][v] = z;
        mp[v][u] = z;
    }

    vector<int> dist(n + 1, inf), cnt(n + 1, 0);
    vector<int> pre(n + 1, 0), pree(n + 1, 0);
    struct e
    {
        int dis, u, p, id;
    };

    queue<e> q;
    q.push({0, 1, 0, 0});
    while(!q.empty())
    {
        auto [dis, u, p, id] = q.front();
        q.pop();
        if(dis < dist[u])
        {
            dist[u] = dis;
            cnt[u] = cnt[p] + mp[u][p];
            pre[u] = p;
            pree[u] = id;
        }
        else if(dis == dist[u])
        {
            if(cnt[p] + mp[u][p] > cnt[u])
            {
                cnt[u] = cnt[p] + mp[u][p];
                pre[u] = p;
                pree[u] = id;
            }
        }

        for(auto &[v, id] : adj[u])
        {
            if(dist[u] + 1 <= dist[v])
            {
                q.push({dist[u] + 1, v, u, id});
            }
        }
    }

    int cur = n;
    while(cur != 1)
    {
        tag[pree[cur]] = 1;
        cur = pre[cur];
    }
    debugarr(pre);

    vector<tuple<int, int, int>> ans;
    for (int i = 0; i < m;i++)
    {
        auto &[u, v, z] = edges[i];
        if(tag[i] == 0 && z == 1)
        {
            ans.emplace_back(u, v, 0);
            // cout << u << " " << v << " " << 0 << "\n";
        }
        else if(tag[i] == 1 && z == 0)
        {
            ans.emplace_back(u, v, 1);

            // cout << u << " " << v << " " << 1 << "\n";
        }
    }
    cout << ans.size() << "\n";
    for(auto &[u, v, z] : ans)
        cout << u << " " << v << " " << z << "\n";
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}