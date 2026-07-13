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

// 每次应该选择当前区间能贡献最大的翻转
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    if (n == 1)
    {
        cout << 0 << "\n";
        return;
    }

    priority_queue<i64, vector<i64>, greater<i64>> pqmin;
    priority_queue<i64, vector<i64>, less<i64>> pqmax;

    i64 cnt = 0;
    int r = m + 1;
    if (r <= n)
    {
        i64 cur = 0;
        while(r <= n)
        {
            cur += a[r];
            pqmin.push(a[r]);
            if(cur < 0)
            {
                i64 tmp = pqmin.top();
                pqmin.pop();
                cur -= 2 * tmp;
                cnt++;
            }
            r++;
        }
    }

    int l = m;
    if(l >= 2)
    {
        i64 cur = 0;
        while(l >= 2)
        {
            cur += a[l];
            pqmax.push(a[l]);
            if(cur > 0)
            {
                i64 tmp = pqmax.top();
                pqmax.pop();
                cur -= 2 * tmp;
                cnt++;
            }
            l--;
        }
    }

    cout << cnt << "\n";
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