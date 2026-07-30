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

int a[] = {4, 8, 15, 16, 23, 42};
void solve()
{
    auto query = [](int i, int j) -> i64
    {
        cout << "? " << i << " "  << j << endl;
        i64 res;
        cin >> res;
        return res;
    };

    vector<int> dbug;
    map<int, array<int, 2>> mp;
    for (int i = 0; i < 6;i++)
        for (int j = i + 1; j < 6;j++)
        {
            int cur = a[i] * a[j];
            mp[cur] = {a[i], a[j]};
        }

    // sort(dbug.begin(), dbug.end());

    // debugarr(dbug)

    vector<int> q(4);
    q[0] = query(1, 2), q[1] = query(3, 4), q[2] = query(2, 5), q[3] = query(3, 5);
    vector<int> ans(7, 0);
    vector<int> cnt(43, 0);
    auto [l, r] = mp[q[0]];
    cnt[l]++, cnt[r]++;
    auto [x, y] = mp[q[2]];
    cnt[x]++, cnt[y]++;
    if(cnt[l] == 2)
    {
        ans[2] = l;
        ans[1] = r;
        if(x != l)
            ans[5] = x;
        else
            ans[5] = y;
    }
    else
    {
        ans[2] = r;
        ans[1] = l;
        if(x != r)
            ans[5] = x;
        else
            ans[5] = y;
    }

    auto [c, d] = mp[q[3]];
    if(d != ans[5])
        ans[3] = d;
    else
        ans[3] = c;

    auto [e, f] = mp[q[1]];
    debug(q[1])
    debug(e)debug(f)
    if(e != ans[3])
        ans[4] = e;
    else
        ans[4] = f;

    vector<int> vis(43, 0);
    for (int i = 1; i <= 5;i++)
        vis[ans[i]] = 1;
    for (int i = 0;i < 6;i++)
    {
        if(!vis[a[i]])
        {
            ans[6] = a[i];
            break;
        }
    }

    cout << "! ";
    for (int i = 1; i <= 6;i++)
        cout << ans[i] << " ";
    cout << endl;
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