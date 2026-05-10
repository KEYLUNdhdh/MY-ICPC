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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);

    for (int i = 1; i <= m;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> ans(n + 1, 0);
    vector<int> d(n + 1, -1);
    deque<int> q;
    
    q.push_back(1);
    d[1] = 0;
    ans[1] = n;
    while(!q.empty())
    {
        int u = q.front();
        q.pop_front();

        for(int v : adj[u])
        {
            if(d[v] == -1)
            {
                d[v] = d[u] + 1;
                ans[v] = n - d[v];
                q.push_back(v);
            }
        }
    }

    // debugarr(ans)

    vector<pii> st;
    for (int i = 1; i <= n;i++)
        st.push_back({d[i], i});
    sort(st.begin(), st.end(), greater<pii>());

    for (int i = 0; i < n;i++)
    {
        auto &[dis, u] = st[i];
        
        for(int v : adj[u])
        {
            if(dis >= d[v])
                chmax(ans[u], n - d[v]);
            else
                chmax(ans[u], ans[v]);
        }

    }

    for (int i = 1; i <= n;i++)
        cout << ans[i] << " ";
    cout << "\n";
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