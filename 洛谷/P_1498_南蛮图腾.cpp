#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<string> s;
    s.push_back(" /\\ ");
    s.push_back("/__\\");
    // for (auto it : s)
    // {
    //     cout << it << "\n";
    // }
    int n;
    cin >> n;
    n--;
    for (int i = 0; i < n;i++)
    {
        int len = s.size();
        int space = pow(2, n - 1) - 2;
        for (int j = 0; j < len;j++)
        {
            s.push_back(s[j] + s[j]);
            s[j] = string(len, ' ') + s[j] + string(len, ' ');
        }
    }
    for (auto it : s)
    {
        cout << it << "\n";
    }
}
