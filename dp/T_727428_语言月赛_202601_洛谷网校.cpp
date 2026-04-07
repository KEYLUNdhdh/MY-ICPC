#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
const int MAXN = 1e5 + 5;
const int INF = 2e18;
struct node{
    int s, t;
    bool operator>=(const node& b) const
    {
        return s >= b.s;
    }
    bool operator<(const node& b) const
    {
        return s < b.s;
    }
};
vector<node> a[MAXN];
int dp[MAXN];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int c, s, t;
    for (int i = 1; i <= n;i++)
    {
        cin >> c;
        for (int j = 0; j < c;j++)
        {
            cin >> s >> t;
            a[i].push_back({s, t});
        }
    }
    dp[1] = a[1][0].t;
    for (int i = 2; i <= n;i++)
    {
        node tp = {dp[i - 1], INF};
        auto it = upper_bound(a[i].begin(), a[i].end(), tp);
        if(it != a[i].end())
            dp[i] = it->t;
        else
        {
            cout << -1;
            return 0;
        }
    }
    cout << dp[n];
}