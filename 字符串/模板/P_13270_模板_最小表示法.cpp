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

int minRep(const string &s)
{
    int n = s.length();
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n)
    {
        int ni = i + k;
        if(ni >= n)
            ni -= n;
        int nj = j + k;
        if(nj >= n)
            nj -= n;

        if(s[ni] == s[nj])
            k++;
        else
        {
            if(s[ni] > s[nj])
                i += k + 1;
            else
                j += k + 1;
            
            if(i == j)
                j++;
            k = 0;
        }
    }
    return min(i, j);
}

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int pos = minRep(s);
    for (int i = 0; i < n;i++)
    {
        int idx = (i + pos) % s.length();
        cout << s[idx];
    }
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