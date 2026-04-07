#include <bits/stdc++.h>
#define ld long double
using namespace std;
ld px, py, ax, ay, bx, by;

bool check(ld p)
{
    ld disa = ax * ax + ay * ay;//原点到a的平方
    ld disb = bx * bx + by * by;//原点到b的平方
    ld pdisa = (px - ax) * (px - ax) + (py - ay) * (py - ay);
    ld pdisb = (px - bx) * (px - bx) + (py - by) * (py - by);
    ld disab = (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
    if (disa > p * p && disb > p * p || pdisa > p * p && pdisb > p * p)
        return false;
    if (disa <= p * p && pdisa <= p * p)
        return true;
    if (disb <= p* p && pdisb <= p * p)
        return true;
    if (disab <= 4 * p * p)
        return true;
    else
        return false;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> px >> py >> ax >> ay >> bx >> by;
        ld l = 0;
        ld r = 1e5;
        while (r - l > 1e-8)
        {
            ld mid = (l + r) / (ld)2.0;
            if (check(mid))
                r = mid;
            else 
                l = mid;
        }
        cout << fixed << setprecision(10) << r << "\n";
    }
}