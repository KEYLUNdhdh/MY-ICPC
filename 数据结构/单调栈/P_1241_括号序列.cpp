#include <bits/stdc++.h>
using namespace std;
typedef struct cha{
    int id;
    char c;
}cha;
deque<cha> d;
int main()
{
    string s;
    cin >> s;
    vector<int> vec(s.size(), 0);
    char ch;
    for (int i = 0; i < s.size();i++)
    {
        ch = s[i];
        cha tp;
        if(ch == '(' || ch == '[')
        {
            tp.c = ch;
            tp.id = i;
            d.push_back(tp);
        }
        else if (ch == ')')
        {
            if(!d.empty() && d.back().c == '(')
            {
                vec[d.back().id] = 1;
                vec[i] = 1;
                d.pop_back();
            }
        }
        else if (ch == ']')
        {
            if(!d.empty() && d.back().c == '[')
            {
                vec[d.back().id] = 1;
                vec[i] = 1;
                d.pop_back();
            }
        }
    }
    for (int i = 0; i < s.size();i++)
    {
        if(s[i] == '(')
        {
            if (vec[i] == 1)
            {
                cout << s[i];
            }
            else
            {
                cout << "()";
            }
        }
        else if(s[i] == '[')
        {
            if(vec[i] == 1)
            {
                cout << s[i];
            }
            else
            {
                cout << "[]";
            }
        }
        else if(s[i] == ')')
        {
            if(vec[i] == 1)
            {
                cout << s[i];
            }
            else
            {
                cout << "()";
            }
        }
        else
        {
            if(vec[i] == 1)
            {
                cout << s[i];
            }
            else
            {
                cout << "[]";
            }
        }
    }
}