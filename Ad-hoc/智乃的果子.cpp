#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
const int MOD = 1e9 + 7;
struct app{
    int c, w;
};
void solve()
{
    int n;
    cin >> n;
    map<i64, i64> mp;
    for (int i = 0; i < n;i++)
    {
        i64 c, w;
        cin >> c >> w;
        mp[w] += c;
    }
    i64 ans = 0;
    i64 rem = 0;
    while(1)
    {
        auto it = mp.begin();
        i64 c = it->second;
        i64 w = it->first;
        if(c >= 1 || rem)
        {
            if(rem)
            {
                mp[w] -= 1;
                ans = (ans + rem + w) % MOD;
                if(mp[w] == 0)
                    mp.erase(it);
                mp[rem + w]++;
                rem = 0;
                continue;
            }
            else if(c >= 2)
            {
                i64 v = c / 2;
                mp[w] -= v * 2;
                if(mp[w] == 0)
                    mp.erase(it);
                ans = (ans + w * 2 * v) % MOD;
                mp[2 * w] += v;
            }
        }
        if(c == 1)
        {
            if(mp.size() <= 1)
                break;
            rem = w;
            mp.erase(it);
        }
    }
    cout << ans % MOD;
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