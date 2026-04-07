#include <iostream>
using namespace std;
#define int long long
int a[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
signed main()
{
    for (int i = 0; i < 25;i++)
    {
        cout << "? " << a[i] << endl;
        cout.flush();
        int g;
        cin >> g;
        if (g == 1)
        {
            cout << "! " << a[i] << endl;
            cout.flush();
            break;
        }
        else
        {
            continue;
        }
    }
}