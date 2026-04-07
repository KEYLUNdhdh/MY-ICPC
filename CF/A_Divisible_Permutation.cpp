#include <bits/stdc++.h>
using namespace std;
int a[200];
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        if(n % 2 == 0)
        {
            n--;
            int dis = (n - 1) / 2;
            int p1 = dis + 1;
            cout << p1 << " ";
            for (int i = 1; i <= dis;i++)
            {
                cout << p1 + i << " " << p1 - i << " ";
            }
            cout << p1 + dis + 1;
            cout << "\n";
        }
        else
        {
            int dis = (n - 1) / 2;
            int p1 = dis + 1;
            cout << p1 << " ";
            for (int i = 1; i <= dis;i++)
            {
                cout << p1 + i << " " << p1 - i << " ";
            }
            cout << "\n";
        }
    }
}