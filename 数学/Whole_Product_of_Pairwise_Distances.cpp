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
    int n;
    cin >> n;
    vector<int> a(n), c(n, 0);
    vector<i64> fac(n, 1);
    for (int i = 1; i < n;i++)
        fac[i] = fac[i - 1] * i % n;
    for (int i = 1; i < n;i++)
        fac[i] = fac[i - 1] * fac[i] % n;

    int f = 0;
    for (int i = 0; i < n;i++)
        cin >> a[i];

    sort(a.begin(), a.end());
    for (int i = 0; i < n;i++)
    {
        a[i] %= n;
        c[a[i]]++;
        if(c[a[i]] > 1 && !f)
        {
            f = 1;
            cout << 0 << "\n";
        }
    }

    if(f)
        return; 

    vector<int> tmp;
    int cnt = 0;
    auto mergeSort = [&](auto self, int l, int r) -> void
    {
        if(l >= r)
            return;

        int m = l + r >> 1;
        self(self, l, m);
        self(self, m + 1, r);
        tmp.assign(r - l + 1, 0);
        int i = l, j = m + 1, idx = 0;
        while(i <= m && j <= r)
        {
            if(a[i] > a[j])
            {
                tmp[idx++] = a[j++];
                cnt += m - i + 1;
            }
            else
                tmp[idx++] = a[i++];
        }

        while(i <= m)
            tmp[idx++] = a[i++];
        while(j <= r)
            tmp[idx++] = a[j++];

        for (int i = 0; i < r - l + 1;i++)
            a[l + i] = tmp[i];
    };

    mergeSort(mergeSort, 0, n - 1);
    if(cnt & 1)
        cout << (-fac[n - 1] + n) % n << "\n";
    else
        cout << fac[n - 1] << "\n";
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