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

void solve()
{
    int n, m;
    cin >> n >> m;
    
    vector<int> tag(n + 1, 0);
    vector<vector<int>> cmp(n + 1, vector<int>(n + 1, 0));
    while(m--)
    {
        int o, i, j;
        cin >> o >> i >> j;

        if(o == 1)
            cmp[i][j] = 1;
        else
            cmp[i][j] = -1;
    }

    for (int i = 1; i <= n;i++)
        tag[i] = cmp[i][i];

    vector<vector<int>> adj(n + 1);
    vector<int> ind(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        for (int j = i + 1; j <= n;j++)
        {
            if(cmp[i][j] == 1)
            {
                if(tag[i] == -1 && tag[j] == -1)
                {
                    cout << "NO\n";
                    return;
                }
                else if(tag[i] == 1 && tag[j] == 1)
                    continue;
                else if(tag[i] == 1 && tag[j] == -1)
                    adj[i].push_back(j), ind[j]++;
                else
                    adj[j].push_back(i), ind[i]++;
            }
            else
            {
                if(tag[i] == 1 && tag[j] == 1)
                {
                    cout << "NO\n";
                    return;
                }
                else if(tag[i] == -1 && tag[j] == -1)
                    continue;
                else if(tag[i] == 1 && tag[j] == -1)
                    adj[j].push_back(i), ind[i]++;
                else
                    adj[i].push_back(j), ind[j]++;
            }
        }
    }

    vector<int> ans(n + 1, 0);
    queue<int> q;
    for (int i = 1; i <= n;i++)
        if(ind[i] == 0)
            q.push(i);

    int res = n;
    int cnt = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        ans[u] = res--;
        ans[u] *= tag[u];
        cnt++;
        for(int v : adj[u])
        {
            ind[v]--;
            if(ind[v] == 0)
                q.push(v);
        }
    }
    if(cnt < n)
    {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
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