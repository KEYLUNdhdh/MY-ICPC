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

uint64_t rnd_state = 1145141919810ULL; 
inline uint32_t fast_rnd() {
    rnd_state ^= rnd_state << 13;
    rnd_state ^= rnd_state >> 7;
    rnd_state ^= rnd_state << 17;
    return rnd_state;
}

const int MAXN = 5e5 + 5;
int a[MAXN], vis[MAXN];
vector<int> pos[MAXN];

// 超级无敌牛逼随机化优化
void solve()
{
    int n, q;
    cin >> n >> q;

    // vector<int> a(n + 1, 0);
    // vector<vector<int>> pos(n + 1);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    // vector<int> vis(n + 1, -1);
    while(q--)
    {
        int l, r, k;
        cin >> l >> r;
        k = 2;
        int ans = 0;
        
        // 提取到循环外，避免在循环内反复计算
        uint32_t len = r - l + 1; 
        int lb = len / k + 1;
        int ub = 24; 
        
        for (int i = 1; i <= ub; i++)
        {
            // 黑魔法 1：Lemire 取模法，用一次乘法和位移干掉巨慢的 '%' 运算符
            uint32_t ck = ((uint64_t)fast_rnd() * len) >> 32;
            int num = a[l + ck];
            
            if(vis[num] == q + 1)
                continue;
            vis[num] = q + 1;
            
            // 黑魔法 2：神级 O(1) 剪枝，如果全局总个数都不够，连二分都免了！(省去大量时间)
            if (pos[num].size() < lb) 
                continue;
            
            auto ll = lower_bound(pos[num].begin(), pos[num].end(), l);
            int t = pos[num].end() - ll;
            
            if(t < lb)
                continue;
            else
            {
                int rr = *(ll + lb - 1);
                if(rr <= r)
                {
                    ans = num;
                    break;
                }
            }
        }
        cout << ans << "\n";
    }

}

bool ED;
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