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
void mergeSort(vector<int> &a,int l,int r, vector<int> &tmp)
{
    if(l >= r)
        return;
    int mid = l + (r - l) / 2;
    mergeSort(a, l, mid, tmp);
    mergeSort(a, mid + 1, r, tmp);
    int i = l, j = mid + 1;
    int idx = 0;
    while(i <= mid && j <= r)
    {
        if (a[i] <= a[j])
        {
            tmp[idx++] = a[i++];
        }
        else
        {
            tmp[idx++] = a[j++];
        }
    }
    while(i <= mid)
        tmp[idx++] = a[i++];
    while(j <= r)
        tmp[idx++] = a[j++];
    for (int k = 0; k < idx;k++)
        a[l + k] = tmp[k];
}
void solve()
{
    int n;
    cin >> n;

    auto query = [&](int u, int v) -> int
    {
        cout << "Q " << u << " " << v << "\n";
        cout.flush();
        int c;
        cin >> c;
        return c;
    };

    vector<int> a(n);
    vector<int> tmp(n, 0);
    iota(a.begin(), a.end(), 1);
    auto mergeSort = [&](auto self, vector<int> &a, int l, int r, vector<int> &tmp) -> void
    {
        if(l >= r)
            return;
        int mid = l + (r - l) / 2;
        self(self, a, l, mid, tmp);
        self(self, a, mid + 1, r, tmp);
        int i = l, j = mid + 1;
        int idx = 0;
        while(i <= mid && j <= r)
        {
            if (query(a[i], a[j]) == 1)
            {
                tmp[idx++] = a[i++];
            }
            else
            {
                tmp[idx++] = a[j++];
            }
        }
        while(i <= mid)
            tmp[idx++] = a[i++];
        while(j <= r)
            tmp[idx++] = a[j++];
        for (int k = 0; k < idx;k++)
            a[l + k] = tmp[k];
    };

    mergeSort(mergeSort, a, 0, n - 1, tmp);

    for (int i = 1;i < n;i++)
    {
        if(query(a[i], a[i - 1]))
        {
            cout << "A 1" << "\n";
            cout.flush();
            return;
        }
    }
    cout << "A 0" << "\n";
    cout.flush();
    return;
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}