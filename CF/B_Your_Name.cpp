#include <bits/stdc++.h>
using namespace std;
int len;
void sort1(string& s1)
{
    for (int i = 0; i < len - 1;i++)
    {
        for (int j = 0; j < len - 1 - i;j++)
        {
            if(s1[j] < s1[j + 1])
            {
                char c = s1[j];
                s1[j] = s1[j + 1];
                s1[j + 1] = c;
            }
        }
    }
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> len;
        string s1, s2;
        cin >> s1 >> s2;
        sort1(s1);
        sort1(s2);
        if(s1 == s2)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}