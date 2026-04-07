#include <bits/stdc++.h>
// #define ld long double
#define int long long
using namespace std;
const int N = 1e5 + 5;
int k[N];
int n, m;
void check(int a,int b, int c)
{
    if(a * c < 0)
    {
        cout << "NO\n";
        return;
    }
    int l = -1;
    int r = n;
    while(l + 1 != r)
    {
        int mid = l + r >> 1;
        if(k[mid] < b)
            l = mid;
        else
            r = mid;
    }
    if (r < n && (b - k[r]) * (b - k[r]) - 4 * a * c < 0)
    {
        cout << "YES\n"
             << k[r] << "\n";
    }
    else if(l > -1 && (b - k[l]) * (b - k[l]) - 4 * a *c < 0)
    {
        cout << "YES\n"
            << k[l] << "\n";
    }
    else
    {
        cout << "NO\n";
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
   
    int a, b, c;
    while(t--)
    {
        cin >> n >> m;
        for (int i = 0; i < n;i++)
            cin >> k[i];
        sort(k, k + n);
        while(m--)
        {
            cin >> a >> b >> c;
            check(a, b, c);
        }
        cout << "\n";
    }
}