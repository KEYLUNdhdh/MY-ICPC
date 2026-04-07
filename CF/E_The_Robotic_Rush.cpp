#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N], b[N],l[N],r[N];
int n, m, k;
int dead[N];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    string s;
    
    while(t--)
    {
        cin >> n >> m >> k;
        vector<vector<int>> dl,dr;
        dl.resize(k + 1);
        dr.resize(k + 1);
        for (int i = 0; i < n;i++)
        {
            dead[i] = 0;
        }
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < m;i++)
            cin >> b[i];
        sort(a, a + n);
        sort(b, b + m);
        int cur = 0;
        int alive = n;
        for (int i = 0; i < n;i++)
        {
            auto it = lower_bound(b, b + m, a[i]);
            if(it != b + m)
            {
                    if(*it - a[i] <= k)
                    {
                        dr[*it - a[i]].push_back(i);
                    }
            }
            if(it != b)
            {
                it--;
                if (a[i] - *it <= k)
                {
                    dl[a[i] - *it].push_back(i);
                }
            }
        }
        cin >> s;
        int minn = 0;
        int maxx = 0;
        for (int i = 0; i < k;i++)
        {
            if(s[i] == 'L')
                cur--;
            else
                cur++;
            if(cur < minn)
            {
                minn = cur;
                int dis = -minn;
                if(dis <= k)
                {
                    for(auto id : dl[dis])
                    {
                        if(!dead[id])
                        {
                            dead[id] = 1;
                            alive--;
                        }
                    }
                }
            }
            if(cur > maxx)
            {
                maxx = cur;
                int dis = maxx;
                if(dis <= k)
                {
                    for(auto id : dr[dis])
                    {
                        if(!dead[id])
                        {
                            dead[id] = 1;
                            alive--;
                        }
                    }
                }
            }
            cout << alive << " ";
        }
        cout << "\n";
    }
}