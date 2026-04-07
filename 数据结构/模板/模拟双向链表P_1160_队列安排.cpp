#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
typedef struct stu{
    int l, r;
    int ava = 1;
}stu ;
stu s[N] = {0};
int main()
{
    int n;
    cin >> n;
    s[1].l = 0;
    s[0].r = 1;
    int k, p;
    for (int i = 2; i <= n;i++)
    {
        cin >> k >> p;
        if(p == 1)  
        {
            s[i].r = s[k].r;
            s[i].l = k;
            s[k].r = i;
            s[s[i].r].l = i;
        }
        else
        {
            s[i].l = s[k].l;
            s[i].r = k;
            s[k].l = i;
            s[s[i].l].r = i;
        }
    }
    int m;
    cin >> m;
    int x;

    for (int i = 0; i < m;i++)
    {   
        cin >> x;
        s[x].ava = 0;
    }
    int st = s[0].r;
    while(st != 0)
    {
        if(s[st].ava)
        cout << st << " ";
        st = s[st].r;
    }
    return 0;
}