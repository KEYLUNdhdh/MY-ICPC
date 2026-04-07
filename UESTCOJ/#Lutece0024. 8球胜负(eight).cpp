#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    while (n != 0)
    {
        string s;
        cin >> s;
        int sumy = 0;
        int sumr = 0;
        for (int i = 0; i < s.size();i++)
        {
            if (s[i] == 'R')
                sumr++;
            else if (s[i] == 'Y')
                sumy++;
            else if (s[i] == 'B')
            {
                if (sumr == 7)
                {
                    cout << "Red\n";
                }
                else
                {
                    cout << "Yellow\n";
                }
            }
            else
            {
                if (sumy == 7)
                {
                    cout << "Yellow\n";
                }
                else
                {
                    cout << "Red\n";
                }
            }
        }
        cin >> n;
    }
}