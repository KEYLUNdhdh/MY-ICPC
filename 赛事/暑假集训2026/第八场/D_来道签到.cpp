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
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

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
bool ST;
constexpr i64 MOD = 998244353, INF = 1e9;

/*

随机化冲不过去啊，草
欧耶，我有顽强拼搏奖
不是，随机化包有道理的，太几把难调了

随机化总结：
根据 k 动态调整大小。
vis 数组防止重复查找。
将两次边界二分优化为一次二分
*/
void solve()
{
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1, 0);
    vector<vector<int>> pos(n + 1);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }

    vector<int> vis(n + 1, -1);
    while(q--)
    {
        int l, r, k;
        cin >> l >> r >> k;
        int ans = INF;
        int cnt = 0;
        int ub;
        if(k == 2)
            ub = 25;
        else if(k == 3)
            ub = 40;
        else if(k == 4)
            ub = 60;
        else
            ub = 90;
        for (int i = 1; i <= ub;i++)
        {
            int ck = rnd() % (r - l + 1);
            int num = a[l + ck];
            if(num >= ans)
                continue;
            if(vis[num] == q)
                continue;
            vis[num] = q;
            auto ll = lower_bound(pos[num].begin(), pos[num].end(), l);
            int t = pos[num].end() - ll;
            int lb = (r - l + 1) / k + 1;
            if(t < lb)
                continue;
            else
            {
                int rr = *(ll + lb - 1);
                if(rr <= r)
                    chmin(ans, num);
            }
        }
        if(ans == INF)
            cout << -1 << "\n";
        else
            cout << ans << "\n";
    }

}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    while(T--)
        solve();
    return 0;
}