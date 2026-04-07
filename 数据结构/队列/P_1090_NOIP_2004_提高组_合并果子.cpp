#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e4 + 5;
int a[N] = {0};
signed main()
{
    priority_queue<int, vector<int>, greater<>> queue;//队头是最小的
    int n;
    int temp;
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        cin >> temp;
        queue.push(temp);
    }
    // sort(a, a + n);
    int ans = 0;
    while(queue.size() != 1)
    {
        int t1 = queue.top();
        queue.pop();
        int t2 = queue.top();
        queue.pop();
        ans += t1 + t2;
        queue.push(t1 + t2);
    }
    // ans -= a[0];
    cout << ans;
}