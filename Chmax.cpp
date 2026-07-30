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

void solve()
{
    int n;
    cin >> n;

    // vector<int> pa(n + 1, -1);
    vector<int> p(n + 1, 0);
    vector<int> vis(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> p[i];

    vector<int> stk;
    stk.push_back(p[1]);
    vis[p[1]] = 1;
    
    for (int i = 2; i <= n;i++)
    {
        if(stk.back() < p[i])
            stk.push_back(p[i]), vis[p[i]] = 1;
    }
    int ans = stk.size();



    vector<int> tmp = {0};
    for (int i = 1; i <= n;i++)
        if(!vis[p[i]])
            tmp.push_back(p[i]);
    swap(p, tmp);
    n = p.size() - 1;
    // debugarr(p) debug(n)
    vector<int> tail(n + 1, INF);
    tail[0] = 0;
    // debug(n)
    for (int i = 1; i <= n;i++)
    {
        auto it = lower_bound(tail.begin(), tail.end(), p[i]) - tail.begin();
        if(it == 1)
        {
            if(p[i] < tail[it])
                tail[it] = p[i];
        }
        else
        {
            it--;
            // pa[p[i]] = tail[it];
            tail[it + 1] = p[i];
        }
    }
    // debug(n)
    for (int i = n; i >= 1;i--)
    {
        if(tail[i] != INF)
        {
            ans += i;
            break;
        }
    }

    cout << ans;
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