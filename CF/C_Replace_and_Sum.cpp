#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int a[MAXN];
int b[MAXN];
int prefix[MAXN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); 
    int t;
    cin >> t;
    while(t--)
    {
        int n, q;
        cin >> n >> q;
        prefix[0] = 0;
        for (int i = 1; i <= n;i++)
            cin >> a[i];
        for (int i = 1; i <= n;i++)
            cin >> b[i];
        for (int i = 1; i <= n;i++)
        {
            if(b[i] > a[i])
                a[i] = b[i];
        }
        for (int i = n; i >= 2;i--)
        {
            if(a[i] > a[i - 1])
                a[i - 1] = a[i];
        }
        for (int i = 1; i <= n;i++)
        {
            if(b[i] > a[i])
                a[i] = b[i];
        }
        for (int i = n; i >= 2;i--)
        {
            if(a[i] > a[i - 1])
                a[i - 1] = a[i];
        }
        for(int i = 1;i <= n;i++)
        {
            prefix[i] = prefix[i - 1] + a[i];
        }
        int l, r;
        while(q--)
        {
            cin >> l >> r;
            cout << prefix[r] - prefix[l - 1] << " ";
        }
        cout << "\n";
    }
}