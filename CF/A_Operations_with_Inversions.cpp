#include <bits/stdc++.h>
using namespace std;
int a[200] = {0};
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n;i++)
            cin >> a[i];
        int len = 0;
        vector<int> vec;
        int sum = 0;
        int maxx = 0;
        int flag = 0;
        for (int i = 0; i < n;i++)
        {
            if (a[i] > maxx)
            {
                flag = 1;
                maxx = a[i];
                continue;
            }
            if (maxx > a[i])
                len++;
            if (flag)
            {
                flag = 0;
                sum += len;
                len = 0;
            }
            
        }
        if (len != 0)
            sum += len;
        cout << sum << "\n";
    }
}