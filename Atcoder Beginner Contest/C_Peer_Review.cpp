#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int a[MAXN];
inline long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    k = min(k, n - k);
    long long res = 1;  
    for (int i = 1; i <= k; ++i) {
        res = res * (n - k + i) / i; 
    }
    return res;
}
int main()
{
    int n, m;
    cin >> n >> m;
    int x, y;
    for (int i = 0; i < m;i++)
    {
        cin >> x >> y;
        a[x]++, a[y]++;
    }
    for (int i = 1; i <= n;i++)
    {
        int res = n - a[i] - 1;
        if(res  < 3)
        {
            cout << 0 << " ";
        }
        else
        {
            cout << comb(res, 3) << " ";
        }
    }
}