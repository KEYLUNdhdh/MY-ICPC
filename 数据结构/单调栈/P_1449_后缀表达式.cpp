#include <bits/stdc++.h>
#define int long long
using namespace std;
deque<int> d;
signed main()
{
    char ch;
    int tp = 0;
    while(1)
    {
        ch = getchar();
        if(ch == '@')
        {
            break;
        }
        else if(ch >= '0' && ch <= '9')
        {
            tp = tp * 10 + ch - '0';
            continue;
        }
        else if(ch == '.')
        {
            d.push_back(tp);
            tp = 0;
            continue;
        }
        else if(ch == '-')
        {
            int l = d.back();
            d.pop_back();
            int f = d.back();
            d.pop_back();
            int res = f - l;
            d.push_back(res);
        }
        else if(ch == '*')
        {
            int l = d.back();
            d.pop_back();
            int f = d.back();
            d.pop_back();
            int res = f * l;
            d.push_back(res);
        }
        else if(ch == '+')
        {
            int l = d.back();
            d.pop_back();
            int f = d.back();
            d.pop_back();
            int res = f + l;
            d.push_back(res);
        }
        else if(ch == '/')
        {
            int l = d.back();
            d.pop_back();
            int f = d.back();
            d.pop_back();
            int res = f / l;
            d.push_back(res);
        }
    }
    cout << d.front();
}