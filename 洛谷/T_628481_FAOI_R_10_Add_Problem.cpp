#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int a[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n;i++)
        cin >> a[i];
    sort(a, a + n);
    int dis = a[n - 1] - a[0];
    int cnt = (dis + m - 1) / m;
    cout << cnt;
}