#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        string s;
        cin >> s;
        vector<int> res;
        int i = 0;
        while(i < s.size())
        {
            if(isdigit(s[i]))
            {
                int num = 0;
                while(i < s.size() && isdigit(s[i]))
                {
                    num = num * 10 + s[i] - '0';
                    i++;
                }
                res.push_back(num);
            }
            else
                i++;
        }
        for(auto it : res)
        {
            cout << it << " ";
        }
        cout << "\n";
    }
}