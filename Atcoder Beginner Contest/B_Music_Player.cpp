#include <bits/stdc++.h>
using namespace std;

int main()
{
    int q;
    cin >> q;
    int vol = 0;
    int op = 0;
    int a;
    while(q--)
    {
        cin >> a;
        if(a == 1)
        {
            vol++;
        }
        else if(a == 2)
        {
            if(vol >= 1)
            {
                vol--;
            }
        }
        else
        {
            op = op ^ 1;
        }
        if(vol >= 3 && op)
            cout << "Yes\n";
        else
            cout << "No\n";
    }

}