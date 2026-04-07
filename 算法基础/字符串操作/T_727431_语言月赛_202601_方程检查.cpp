#include <bits/stdc++.h>
#define int long long
using namespace std;
int val[26];

int cal(string t)
{
    int f = 1;
    int sum = 0;
    int i = 0;
    while(i < t.size())
    {
        if(t[i] == '-')
        {
            f = -1;
            i++;
        }
        else if(t[i] == '+')
        {
            f = 1;
            i++;
        }
        else if(t[i] >= 'a' && t[i] <= 'z')
        {
            sum += val[t[i] - 'a'] * f;
            i++;
        }
        else
        {
            int num = 0;
            while(i < t.size() && isdigit(t[i]))
            {
                num = num * 10 + t[i] - '0';
                i++;
            }
            sum += num * f;
        }
    }
    return sum;
} 
signed main()
{
    int q;
    cin >> q;
    while(q--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        for (int i = 1; i <= n;i++)
        {
            string tp;
            cin >> tp;
            char ch = tp[0];
            tp = tp.substr(2);
            val[ch - 'a'] = stoi(tp);
        }
        int pos = s.find('=');
        string l = s.substr(0, pos);
        string r = s.substr(pos + 1);
        if(cal(l) == cal(r))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}