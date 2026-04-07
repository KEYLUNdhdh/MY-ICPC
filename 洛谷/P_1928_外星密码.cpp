#include <bits/stdc++.h>
using namespace std;

string dis()
{
    int k = 0;
    string ans, str;
    string tp = "";
    char ch;
    while (cin >> ch)
    {
        if (ch == '[')
        {
            cin >> k;
            str = dis();
            while (k--)
            {
                ans += str;
            }
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ans += ch;
        }
        else
        {
            return ans;
        }
    }
    return ans;
}

int main()
{
    string ans = dis();
    cout << ans;
}