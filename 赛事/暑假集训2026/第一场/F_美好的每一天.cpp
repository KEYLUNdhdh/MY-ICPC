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
    int n, m;
    cin >> n >> m;

    auto check = [&](string s) -> bool
    {
        string tmp(s.rbegin(), s.rend());
        if(tmp == s)
            return true;
        else
            return false;
    };

    vector<string> ss(n);
    map<string, int> mp;
    int pos = -1;
    int maxx = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> ss[i];
        string p = ss[i];
        mp[p]++;
        if(check(p))
        {
            if(p.size() > maxx)
            {
                maxx = p.size();
                pos = i;
            }
        }
    }

    string ans = "";
    if(pos != -1)
    {
        string c = ss[pos];
        while(mp[c])
            ans += c, mp[c]--;
    }
    for (int i = 0; i < n;i++)
    {
        string s = ss[i];
        string tmp(s.rbegin(), s.rend());
        if(s == tmp)
        {
            int t = mp[s] / 2;
            mp[s] -= t * 2;

            while(t--)
                ans = s + ans + s;
        }
        else
        {
            int t = min(mp[s], mp[tmp]);
            mp[s] -= t, mp[tmp] -= t;
            while(t--)
                ans = tmp + ans + s;
        }
    }

    if(!ans.empty())
        cout << ans.length() << "\n" << ans;
    else
        cout << 0 << "\n";
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