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

struct t
{
    int a, b, d;

    bool operator<(const t &b) const
    {
        return d < b.d;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<t> a(n + 1);
    for (int i = 1; i <= n;i++)
        cin >> a[i].a >> a[i].d >> a[i].b;

    sort(a.begin() + 1, a.end());
    vector<int> cnt(n + 1, 0);
    vector<int> ans(m + 1, 0);

    for (int i = 1; i <= n;i++)
    {
        int co;
        if(a[i].d == 1)
            co = a[i].b;
        else
            co = a[i].a;
        if(cnt[co] == 0)
            ans[1]++;
        cnt[co]++;
    }

    debugarr(cnt)
    int idx = 1;
    int ansp = 2;
    int curans = ans[1];
    debug(curans)
    while(idx <= n)
    {
        while(idx <= n && a[idx].d == 1)
            idx++;

        int nowd = a[idx].d;
        while(ansp < nowd && ansp <= m)
                ans[ansp++] = curans;
        while(idx <= n && a[idx].d == nowd)
        {
            auto [coa, cob, d] = a[idx]; 

            if(cnt[coa] <= 1)
                curans--;
            cnt[coa]--;
            if(cnt[cob] == 0)
                curans++;
            cnt[cob]++;
            idx++;
        }
    }
    debug(curans)
    while(ansp <= m)
        ans[ansp++] = curans;
    for (int i = 1; i <= m;i++)
        cout << ans[i] << "\n";
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
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}