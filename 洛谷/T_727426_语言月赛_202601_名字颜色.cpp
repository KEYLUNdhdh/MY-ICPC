#include <bits/stdc++.h>
using namespace std;

int main()
{
    int sum = 0, tp;
    for (int i = 0; i < 5;i++)
    {
        cin >> tp;
        sum += tp;
    }
    if(sum >= 230)
    {
        cout << "Red";
    }
    else if(sum >= 170)
        cout << "Orange";
    else if(sum >= 120)
        cout << "Green";
    else if(sum >= 100)
        cout << "Blue";
    else
        cout << "Grey";
}