// /扫描线（Sweep Line）结合贪心策略
#include <bits/stdc++.h>
#define pii pair<int,int>
#define int long long
using namespace std;
int n, q;
const int N = 2e5 + 5;
int ans[N] = {0};

bool cmp(pii p1,pii p2)
{
    return (p1.first + p1.second) < (p2.first + p2.second);
}
int check(int x,int y)
{
    return max(0ll, abs(x - y) - 1);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> q;
        vector<pii> vec(n);
        vector<int> dp(n + 5,0);
        int res = 0, zuo = 0, you = 0;
        for (int i = 0; i < n;i++)
        {
            cin >> vec[i].first >> vec[i].second;
            dp[vec[i].first]++;
            if (vec[i].first > 1)
                res += vec[i].first - 1, you++;
        }
        ans[0] = res;
        sort(vec.begin(), vec.end(),cmp);
        int j = 0;
        for (int i = 1; i <= n;i++)
        {
            res += zuo - you;
            zuo += dp[i - 1];
            you -= dp[i + 1];

            while(j < n && vec[j].first + vec[j].second <= 2 * i)
            {
                dp[vec[j].first]--;
                dp[vec[j].second]++;
                res += check(vec[j].second, i) - check(vec[j].first, i);
                if(vec[j].first <= i - 1)
                    zuo--;
                if(vec[j].second > i + 1)
                    you++;
                j++;
            }
            ans[i] = res;
        }
        int x;
        for (int i = 0; i < q;i++)
        {
            cin >> x;
            cout << ans[x] << " ";
        }
        cout << "\n";
    }
}