#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    int p = 1;
    int x;
    while(t--)
    {
        cin >> x;
        while(x--)
        {
            cout << p++ << " ";
        }
        cout << "\n";
    }
}