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
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    map<int, vector<int>> mp;
    for (int i = 0; i < n;i++)
        cin >> a[i], mp[a[i]].push_back(i);

    if(is_sorted(a.begin(), a.end()))
    {
        cout << 0 << "\n";
        return;
    }

    vector<pll> b(n);
    for (int i = 0; i < n;i++)
        b[i].first = a[i], b[i].second = i;
    sort(b.begin(), b.end());

    int k = n + 1;
    int l = 0, r = n + 1;
    auto check = [&](int mid) -> bool
    {
        int len = 1 << __lg(mid);
        len <<= 1;
        if(mid == 0)
            cout << is_sorted(a.begin(), a.end());
        for(int i = 0 ;i < n;i++)
        {
            int ori = b[i].second;
            if(ori / len != i / len)
                return false;
        }
        return true;
    };

    while(l + 1 < r)
    {
        int m = l + r >> 1;
        if(check(m))
            r = m;
        else
            l = m;
    }

    cout << r << "\n";
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