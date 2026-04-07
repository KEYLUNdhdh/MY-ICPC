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

struct cow
{
    int pos, id;
};
void solve()
{
    int n, m;
    cin >> n;
    vector<cow> vec(n);
    vector<int> uni(n);
    vector<int> id;
    for (int i = 0; i < n;i++)
    {
        cin >> vec[i].pos >> vec[i].id;
        uni[i] = vec[i].pos;
        id.push_back(vec[i].id);
    }
    sort(vec.begin(), vec.end(), [](cow a, cow b)
         { return a.pos < b.pos; });
    sort(uni.begin(), uni.end());
    sort(id.begin(), id.end());
    id.erase(unique(id.begin(), id.end()), id.end());
    m =  id.size();
    auto g = [&](int k)
    {
        return lower_bound(uni.begin(), uni.end(), k) - uni.begin();
    };
    auto gid = [&](int k)
    {
        return lower_bound(id.begin(), id.end(), k) - id.begin();
    };
    int l = 0, r = 0;
    int cnt = 0,minn = 1e9;
    vector<int> vis(n + 1, 0);
    for (r = 0; r < n;r++)
    {
        if(!vis[gid(vec[r].id)])
            cnt++;
        vis[gid(vec[r].id)]++;
        while(cnt == m)
        {
            chmin(minn, uni[r] - uni[l]);
            vis[gid(vec[l].id)]--;
            if(vis[gid(vec[l].id)] == 0)
                cnt--;
            l++;
        }
    }
    cout << minn;
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