#include <bits/stdc++.h>
#define ld long double
using namespace std;

ld dis(ld x,ld y,ld m,ld n)
{
    ld ans = (x - m) * (x - m) + (y - n) * (y - n);
    return ans;
}

int main()
{
    ld a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    if(dis(a,b,c,d) == dis(c,d,e,f) && dis(c,d,a,b) == dis(a,b,e,f))
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
}