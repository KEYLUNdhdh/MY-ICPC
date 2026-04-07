#include <bits/stdc++.h>
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
const int MOD = 998244353;
//在树上遍历所有节点并返回起点的最短路径，其规则非常固定：必须经过每条边恰好两次。
// 一次是“进去”子树。
// 一次是“出来”回溯。
// 因此，最小总代价就是：所有边权之和的 2 倍。
//为什么是 2×∑w？ 因为在树中，要从一个点出发去访问某个叶子节点并回来，唯一的路径就是原路返回。每一条边都必须被“踏入”和“退出”各一次。
void solve()
{
    i64 n, m;
    cin >> n >> m;

    i64 ans = 0;
    for (int i = 0; i < n - 1;i++)
    {
        i64 u, v, w;
        cin >> u >> v >> w;
        ans += w;
    }
    cout << ans * 2;
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