#include <bits/stdc++.h>
using namespace std;


int main()
{
    int t;
    cin >> t;
    string a, b;
    while(t--)
    {
        cin >> a >> b;
        int fa = 0,fb = 0;
        if(b.back() == '+')
        {
            fb = 1;
            b.pop_back();
        }
        if(a.back() == '+')
        {
            fa = 1;
            a.pop_back();
        }
        if(b == a)
        {
            if(fa && !fb)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
        else
        {
            if(a.size() > b.size())
                cout << "Yes\n";
            else if (a.size() < b.size())
            {
                cout << "No\n";
            }
            else
            {
                if(a > b)
                {
                    cout << "Yes\n";
                }
                else
                {
                    cout << "No\n";
                }
            }
        }
    }
}