#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
const int MOD = 998244353;

//单调队列 双指针
void solve()
{
    int n, m;
    cin >> n >> m;
    deque<int> d(n + 1, 0);
    vector<int> vis(m + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> d[i];
    int l = 1;
    int r = 1;
    int cnt = 0;
    int ans = 1e9;
    int x = -1, y = n + 1;
    for (r = 1; r <= n;r++)
    {
        if(vis[d[r]] == 0)
            cnt++;
        vis[d[r]]++;
        //在 cnt = m - 1时退出，此时才能正常向右扩展去寻找
        while(cnt == m)
        {
            if(r - l + 1 < ans)
            {
                ans = r - l + 1;
                x = l;
                y = r;
            }
            vis[d[l]]--;
            if(vis[d[l]] == 0)
                cnt--;
            l++;
        }
    }
    cout << x << " " << y;
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