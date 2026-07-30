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
    int n, k;
    cin >> n >> k;
    auto query = [](int pos) -> int
    {
        cout << "? " << pos << endl;
        int res;
        cin >> res;
        return res;
    };

    auto ans = [](int l, int r) -> void
    {
        cout << "! " << l << " " << r << endl;
    };

    auto Nans = []() -> void
    {
        cout << "! " << -1 << endl;
    };

    int idx = 1;
    for (int cnt = 1; cnt <= 250;)
    {
        assert(idx <= k);
        int init = query(idx);
        int up = k;
        int count = 2;
        while(up + idx <= n)
        {
            int tmp = query(up + idx);
            if(tmp != init)
            {
                int lb = count * k;
                int ub = count * (k + 1) - 1;
                int s = idx + up - k + 1;
                if(s == ub)
                {
                    ans(ub, n - ub);
                    return;
                }
                while(s <= ub)
                {
                    int l, r;
                    if(cnt <= 250)
                        l = query(s), cnt++;
                    if(cnt <= 250)
                        r = query(s + k), cnt++;
                    else
                    {
                        Nans();
                        return;
                    }
                    if(l != r)
                    {
                        Nans();
                        return;
                    }
                    s++;
                }
                ans(ub, n - ub);
                return;
            }
            up += k;
            count++;
        }
        idx++;
        cnt++;
    }
    Nans();
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