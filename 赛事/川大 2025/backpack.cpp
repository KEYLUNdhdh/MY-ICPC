#include <bits/stdc++.h>
#define int long long
#define ld long double
using namespace std;
typedef struct rbq {
    int v, w, id;
}rbq;

bool cop(rbq a,rbq b)
{
    return a.w * b.v > a.v * b.w;
}
signed main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int vbag;
        vector<rbq> item(3);
        cin >> vbag;
        for (int i = 0; i < 3;i++)
            cin >> item[i].v >> item[i].w,item[i].id = i;
        sort(item.begin(), item.end(), cop);
        
    }
}