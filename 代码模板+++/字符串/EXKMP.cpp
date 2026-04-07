#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct EXKMP
{
    vector<int> z;
    vector<int> p;

    void get_z(const string& b)
    {
        int m = b.size();
        z.assign(m, 0);
        if(m == 0)
            return;
        z[0] = m;
        for (int i = 1, l = 0, r = -1; i < m;i++)
        {
            if(i <= r && z[i - l] < r - i + 1)
                z[i] = z[i - l];
            else
            {
                z[i] = max(0, r - i + 1);
                while(i + z[i] < m && b[z[i]] == b[i + z[i]])
                    z[i]++;
                
            }
            if(z[i] > r - i + 1)
            {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }

    void get_p(const string& a, const string& b)
    {
        int n = a.size(), m = b.size();
        p.assign(n, 0);
        for (int i = 0, l = 0, r = -1; i < n;i++)
        {
            if(i <= r && z[i - l] < r - i + 1)
                p[i] = z[i - l];
            else
            {
                p[i] = max(0, r - i + 1);
                while(i + p[i] < n && p[i] < m && a[i + p[i]] == b[p[i]])
                    p[i]++;
                
            }
            if(p[i] > r - i + 1)
            {
                l = i;
                r = i + p[i] - 1;
            }
        }
    }
};