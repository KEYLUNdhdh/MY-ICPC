#include <bits/stdc++.h>
using namespace std;
int n;
int a[300005] = {0};



int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t --)
    {
        int n;
        cin >> n;
        int flag = 0;
        cin >> a[0];
        int check = 0;
        int tp = a[0] % 2;
        for (int i = 1; i < n;i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i < n;i++)
        {
             if(a[i] % 2 != tp)
            {
                check = 1;
            }
        }
        if (check)
        {
            sort(a, a + n);
            for (int i = 0; i < n;i++)
                cout << a[i] << " ";
            cout << "\n";
        }
        else
        {
            for (int i = 0; i < n;i++)
                cout << a[i] << " ";
            cout << "\n";
        }
    }   
}