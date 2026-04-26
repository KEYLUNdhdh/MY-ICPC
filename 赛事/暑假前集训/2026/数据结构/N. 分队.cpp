#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline {cerr << "----------------------\n";}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937 rnd(time(0));

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
constexpr int MOD = 998244353, INF = 1e9;

struct node
{
    int l, r, val;
};
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<node> a(n + 2);
    vector<int> pos(n + 1, -1);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i].val;
        pos[a[i].val] = i;
        a[i].l = i - 1;
        a[i].r = i + 1;
    }
    a[0].l = 0, a[n + 1].r = n + 1;
    vector<int> ans(n + 2, 2);
    int key = 1;
    // debugarr(pos)
    int turn = -1;
    while(1)
    {
        turn++;
        int maxpos = -1;
        for (int i = n - turn; i >= 1;i--)
        {
            if(pos[i] != -1)
            {
                maxpos = pos[i];
                pos[i] = -1;
                break;
            }
        }
        // debug(maxpos)
        if(maxpos == -1)
            break;
        ans[maxpos] = key;
        int l = maxpos, r = maxpos;
        for (int i = 0; i < k;i++)
        {
            l = a[l].l;
            if(l == 0)
                break;
            pos[a[l].val] = -1;
            ans[l] = key;
        }
        for (int i = 0; i < k;i++)
        {
            r = a[r].r;
            if(r == n + 1)
                break;
            pos[a[r].val] = -1;
            ans[r] = key;
        }

        a[a[l].l].r = a[r].r;
        a[a[r].r].l = a[l].l;
        key ^= 1;
    }

    for (int i = 1; i <= n;i++)
        cout << (ans[i] == 1 ? 1 : 2);
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