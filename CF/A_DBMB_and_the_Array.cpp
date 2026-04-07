#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n,x , s;
        int sum = 0;
        cin >> n >> s >> x;
        int tp;
        for (int i = 0; i < n;i++)
        {
            cin >> tp;
            sum += tp;
        }
        int dis = s - sum;
        if(dis >= 0 && dis % x == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}