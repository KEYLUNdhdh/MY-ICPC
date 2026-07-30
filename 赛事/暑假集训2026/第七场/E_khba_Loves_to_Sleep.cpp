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
    int n, kk;
    i64 x;
    cin >> n >> kk >> x;

    vector<i64> a(n + 1, 0);
    map<i64, int> vis;
    priority_queue<pll, vector<pll>, less<pll>> pq;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        if(!vis[a[i]])
        {
            pq.push({0, a[i]});
            vis[a[i]] = 1;
        }
    }

    sort(a.begin() + 1, a.end());

    if(a[1] != 0)
    {
        pq.push({a[1], 0});
        vis[0] = 1;
    }
    
    if(a[n] != x)
    {
        pq.push({x - a[n], x});
        vis[x] = 1;
    }

    for (int i = 1; i <= n - 1;i++)
    {
        i64 cur = a[i], nx = a[i + 1];
        i64 dis = nx - cur;
        if(dis < 2)
            continue;
        if(dis % 2 == 0)
        {
            i64 mid = cur + (nx - cur) / 2;
            pq.push({(nx - cur) / 2, mid});
            vis[mid] = 1;
        }
        else
        {
            i64 m1 = cur + (nx - cur) / 2, m2 = m1 + 1;
            i64 len = (nx - cur) / 2;
            pq.push({len, m1}), pq.push({len, m2});
            vis[m1] = 1, vis[m2] = 1;
        }
    }

    vector<i64> ans;

    while(kk > 0 && !pq.empty())
    {
        auto [dis, pos] = pq.top();
        pq.pop();
        ans.push_back(pos);

        i64 l = pos - 1, r = pos + 1;
        if(l >= 0 && !vis[l])
        {
            vis[l] = 1;
            pq.push({dis - 1, l});
        }
        if(r <= x && !vis[r])
        {
            vis[r] = 1;
            pq.push({dis - 1, r});
        }
        kk--;
    }

    sort(ans.begin(), ans.end());
    for(i64 k : ans)
        cout << k << " ";
    cout << "\n";
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
    return 0;
}