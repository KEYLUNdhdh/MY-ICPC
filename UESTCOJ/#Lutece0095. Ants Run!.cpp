#include <iostream>
#include <bits/stdc++.h>
#define pi 3.1415926
using namespace std;
int a[500005] = {0};
int n, r;
int check(double t)
{
    double sumx = 0;
    int prev = a[0];
    for (int i = 1; i < n;i++)
    {
        if(a[i] < prev)
        {
            sumx += (prev -a[i]) * t;
        }
        prev = a[i];
    }
    if (a[0] < prev)
    {
        sumx += (prev - a[0]) * t;
    }
    return (double)sumx <=2 * pi * r;
}
int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> r;
        int flag = 1;
        cin >> a[0];
        for (int i = 1; i < n;i++)
        {
            cin >> a[i];
            if (a[i] != a[0])
                flag = 0;
        }
        if (flag)
        {
            cout << "Inf\n";
            continue;
        }
        double left = 0;
        double right = 1000000.0;
        for (int i = 0; i < 100;i++)
        {
            double mid = (left + right) / 2.0;
            if (check(mid))
            {
                left = mid;
            }
            else
                right = mid;
        }
            cout  << fixed << setprecision(3)<< round(right * 1000) /1000.0<< "\n";
    }
}