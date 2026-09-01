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
    int n;cin >> n;
    deque<i64> a(n);
    for (int i = 0; i < n;i++)
        cin >> a[i];

    sort(a.begin(), a.end());
    deque<i64> p, q;
    for (int i = 0; i < n;i++)
        if(a[i] & 1)
            p.push_back(a[i]);
        else
            q.push_back(a[i]);

    if(p.empty() || q.empty())
    {
        cout << 0 << "\n";
        return;
    }
    debugarr(p) debugarr(q)
    i64 ans = 0;
    while(!q.empty())
    {
        i64 maxji = p.back();
        i64 ft = q.front();
        if(maxji > ft)
        {
            q.pop_front();
            p.push_back(maxji + ft);
            ans++;
        }
        else
        {
            ans += q.size() + 1;
            break;
        }
    }
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
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}