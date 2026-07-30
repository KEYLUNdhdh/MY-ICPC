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
    map<i64, vector<int>> mp;
    queue<pair<i64, int>> q;
    for (int i = 1; i <= n;i++)
    {
        i64 val, p;
        cin >> val, p = val + i - 1;
        if(i > 1)
        {
            mp[p].push_back(i);
            if(p == n)
                q.push({n, i});
        }
    }
    
    if(q.empty())
    {
        cout << n << "\n";
        return;
    }

    i64 ans = n;
    set<int> st;
    while(!q.empty())
    {
        auto [val, pos] = q.front();
        q.pop();
        // cerr << "val:" << val << " " << "pos:" << pos << "\n";
        i64 nxtlen = val + pos - 1;
        chmax(ans, nxtlen);
        auto it = mp.find(nxtlen);
        if(it != mp.end())
        {
            for(int v : mp[nxtlen])
                q.push({nxtlen, v});
                
            mp.erase(it);
        }
    }
    // cutline
    cout << ans << "\n";
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
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}