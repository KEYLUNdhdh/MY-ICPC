#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int ori[N];
int rl[N];
int main()
{
    ios::sync_with_stdio(0);
    int q;
    cin >> q;
    int n;
    while(q--)
    {
        cin >> n;
        for (int i = 0; i < n;i++)
            cin >> ori[i];
        for (int i = 0; i < n;i++)
            cin >> rl[i];
        deque<int> d;
        int index = 0;
        int flag = 0;
        for (int i = 0; i < n;i++)
        {
            d.push_back(ori[i]);
            while(!d.empty() && d.back() == rl[index])
            {
                d.pop_back();
                index++;
            }
        }
        while(!d.empty())
        {
            if(d.back() == rl[index])
            {
                d.pop_back();
                index++;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            cout << "No" << "\n";
        }
        else
        {
            cout << "Yes\n";
        }
    }
}