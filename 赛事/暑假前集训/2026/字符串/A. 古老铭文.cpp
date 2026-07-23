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
    string s;
    cin >> s;

    int n = s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n;i++)
    {
        int j = p[i - 1];
        while(j > 0 && s[i] != s[j])
            j = p[j - 1];
        
        if(s[i] == s[j])
            j++;

        p[i] = j;
    }

    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n;i++)
        cnt[p[i]]++;

    for (int len = n; len >= 1;len--)
        cnt[p[len - 1]] += cnt[len];

    // cnt++ 是因为每个串在开头至少都出现一次
    for (int len = 0; len <= n;len++)
        cnt[len]++;

    vector<int> ans;

    // 根据 p 数组跳着获取每个border
    for (int len = n; len > 0;len = p[len - 1])
        ans.push_back(len);

    reverse(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    
    for(int len : ans)
        cout << len << " " << cnt[len] << "\n";

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