#include <bits/stdc++.h>
#define dubug(x) { cerr << #x << " = " << x << "\n"; }
#define dubugarr(x){        \
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
struct ran
{
    i64 d, s, t;
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> ck(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> ck[i];
    vector<ran> range(m + 1);
    for (int i = 1; i <= m;i++)
        cin >> range[i].d >> range[i].s >> range[i].t;
    auto check = [&](i64 x) -> bool
    {
        vector<i64> dis(n + 5, 0);
        for (int i = 1; i <= x;i++)
        {
            dis[range[i].s] += range[i].d;
            dis[range[i].t + 1] -= range[i].d;
        }
        i64 sum = 0;
        for (int i = 1; i <= n;i++)
        {
            sum += dis[i];
            if(sum > ck[i])
                return false;
        }
        return true;
        
    };
    i64 l = 0, r = m + 1;
    while(l + 1 < r)
    {
        i64 mid = l + r >> 1;
        if(check(mid))
            l = mid;
        else
            r = mid;
    }
    if(l == m)
        cout << 0;
    else
        cout << -1 << "\n" << r;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}