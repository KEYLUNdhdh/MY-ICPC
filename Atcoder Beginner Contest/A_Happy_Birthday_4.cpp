#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x, y, z;
    cin >> x >> y >> z;
    int M = max(x, y);
    int flag = 0;
    for (int i = 0; i <= (100 - M);i++)
    {
        if (z * (y + i) == x + i)
        {
            flag = 1;
            break;
        }
    }
    if(flag)
    {
        cout << "Yes";
        return 0;
    }
    else
        cout << "No";
}