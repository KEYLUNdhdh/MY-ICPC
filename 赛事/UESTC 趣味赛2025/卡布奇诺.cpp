#include  <bits/stdc++.h>
#define int long long
using namespace std;
int mei[1000005] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie();
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n;i++)
            cin >> mei[i];
        mei[n + 1] = 0;
        mei[0] = 0;
        int ans = -1;
        for (int i = 0; i <= n;i++)
        {
            int d = mei[i] ^ mei[i + 1];
            ans = max(ans, d);
        }
        cout << ans << "\n";
    }
    
}