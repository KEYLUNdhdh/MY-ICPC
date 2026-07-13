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
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    multiset<int> st;
    int tmplen = 0;
    int curlen = n;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        if(i != 0 && a[i] != a[i - 1])
        {
            st.insert(tmplen);
            tmplen = 1;
        }
        else
            tmplen++;
    }
    st.insert(tmplen);
    int ans = 0;
    int prev = 0;
    while(!st.empty())
    {
        int ft = *st.begin();
        int sz = st.size();
        i64 dif = k - curlen;
        int den = st.size();
        if(dif % sz == 0)
        {
            i64 delta = dif / sz;
            i64 minn = max<i64>(-delta, prev);
            if(minn < ft)
                ans++;
        }

        int cntft = 0;

        while(!st.empty() && *st.begin() == ft)
        {
            st.erase(st.begin());
            cntft++;
        }

        curlen -= ft * cntft;
        prev = ft;
    }

    cout << ans << "\n";
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