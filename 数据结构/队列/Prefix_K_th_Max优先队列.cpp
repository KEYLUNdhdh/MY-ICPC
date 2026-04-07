#include <bits/stdc++.h>
using namespace std;
int a[1000005] = {0};
void solve()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    priority_queue<int, vector<int>,greater<int>> q;
    for (int i = 1; i <= k;i++)
    {
        q.push(a[i]);
    }
    cout << q.top() << "\n";
    for (int i = k + 1; i <= n;i++)
    {
        if (a[i] > q.top())
        {
            q.pop();
            q.push(a[i]);
        }
        cout << q.top() << "\n";
    }
}
//两种解法
int main()
{
    ios::sync_with_stdio(0);
    // solve();
    int n, k;
    cin >> n >> k;
    int x;
    while (k-- && n--)
    {
        cin >> x;
        a[x] = 1;
    }
    int ans = 0;
    while (!a[ans])
        ans++;
    cout << ans << "\n";
    while (n--)
    {
        cin >> x;
        a[x] = 1;
        if (x > ans)
        while(!a[++ans]);
        cout << ans << "\n";
    }
}