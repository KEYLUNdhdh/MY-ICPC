#include <iostream>
using namespace std;

int main()
{
    int n;cin >> n;
    double temp;
    double sum = 0;
    while (n--)
    {
        for (int i = 0;i < 3;i++)
        {
            cin >> temp;
            sum+= temp;
        }
        double dis = abs(21 - sum);
        double aft = abs(21.0 - (double)sum - 7);
        if (aft < dis) 
        {
            cout << "Yes" << "\n";
        }
        else
        {
            cout << "No" << "\n";
        }
        sum = 0;
    }
}