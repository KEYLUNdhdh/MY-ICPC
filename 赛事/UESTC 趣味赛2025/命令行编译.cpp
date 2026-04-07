#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    cin.ignore();
    while(t--)
    {
        string ori, cpp = "c++17", youhua = "None", output = "a.out";
        vector<string> warn;
        string tp;
        getline(cin, tp);
        stringstream ss(tp);
        string s;
        while (ss >> s)
        {
            if (s == "g++")
                continue;
            if (s[0] != '-')
            {
                ori = s;
            }
            else if(s[1] == 'O')
            {
                youhua = s.substr(1);
            }
            else if(s[1] == 'W')
            {
                warn.push_back(s.substr(1));
            }
            else if(s[1] == 's')
            {
                cpp = s.substr(5);
            }
            else
            {
                output = s.substr(2);
            }
            
        }
        cout << ori << "\n"
                 << cpp << "\n"
                 << youhua << "\n";
            if (warn.empty())
            {
                cout << "None\n";
            }
            else
            {
                for (auto& it : warn)
                {
                    cout << it << " ";
                }
                cout << "\n";
            }
            cout << output << "\n";
    }
}