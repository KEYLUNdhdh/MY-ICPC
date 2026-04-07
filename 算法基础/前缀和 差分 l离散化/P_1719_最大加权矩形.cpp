#include <bits/stdc++.h>
using namespace std;
const int MAXN = 150;
int a[MAXN][MAXN];
int prefix[MAXN][MAXN];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= n;j++)
            cin >> a[i][j];
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= n;j++)
            prefix[i][j] = a[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
    int maxx = -1e9;
    for (int x1 = 1; x1 <= n;x1++)
        for (int y1 = 1; y1 <= n;y1++)
            for (int x2 = x1; x2 <= n;x2++)
                for (int y2 = y1; y2 <= n;y2++)
                {
                    int ans = prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
                    maxx = max(maxx, ans);
                }
    cout << maxx;
}