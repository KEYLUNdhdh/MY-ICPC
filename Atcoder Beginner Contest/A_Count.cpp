#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int cnt = 0;
    for (int i = 0; i < s.size();i++)
    {
        if(s[i] == 'i' || s[i] == 'I' || s[i] == 'j' || s[i] == 'J')
            cnt++;
    }
    cout << cnt;
}