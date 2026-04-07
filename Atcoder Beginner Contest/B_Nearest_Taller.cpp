#include <iostream>
using namespace std;
int a[105] = {0};
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n;i++)
    {
        int pos = -1;
        for (int j = i - 1; j >= 1;j--)
        {
            if (a[j] > a[i])
            {
                pos = j;
                break;
            }
        }
        cout << pos << endl;
    }
}