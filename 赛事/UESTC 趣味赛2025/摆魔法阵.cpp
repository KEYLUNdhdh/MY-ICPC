#include <iostream>
#define int long long
using namespace std;

signed main()
{
    int t;cin >>t;
    int x,y,z;
    int a,b,c;
    while(t--)
    {
    cin >> a >> b >> c >> x >> y >> z;
    if (a > x || b > y || c > z)
    {
        cout << "No" << "\n";
        continue;
    }
    if (x % a == 0 && y % b == 0 && z % c == 0
    || x % a == 0 && y % c == 0 && z % b == 0
    || x % b == 0 && y % a == 0 && z % c == 0
    || x % b == 0 && y % c == 0 && z % a == 0
    || x % c == 0 && y % b == 0 && z % a == 0
    || x % c == 0 && y % a == 0 && z % b == 0)
    {
        cout << "Yes" << "\n";
        continue;
    }
    else
    {
        cout << "No" << "\n";
        continue;
    }
    }
}