#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, h;
const int N = 2e5 + 5;
int a[N],b[N],c[N],res[N];
vector<int> ch;
signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> m >> h;
        for (int i = 1; i <= n;i++)
        {
            cin >> a[i];
            res[i] = a[i];
        }
        for (int i = 0; i < m;i++)
            cin >> b[i] >> c[i];
            int pre = 0;
        for (int i = 0; i < m;i++)
        {
            a[b[i]] += c[i];
            ch.push_back(b[i]);
            if(a[b[i]] > h)
            {
                for(auto k : ch)
                {
                    a[k] = res[k];
                }
                ch.clear();
            }
        }
        for (int i = 1; i <= n;i++)
            cout << a[i] << " ";
        cout << "\n";
        ch.clear();
    }
}

