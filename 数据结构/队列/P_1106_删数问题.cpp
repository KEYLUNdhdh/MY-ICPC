#include <bits/stdc++.h>
using namespace std;
const int N = 300;
int main()
{
    
    string s;
    cin >> s;
    deque<int> res;
    int k;
    cin >> k;
    for (auto ch : s)
    {
        while(k > 0 && !res.empty() && res.back() > (ch - '0'))
        {
            res.pop_back();
            k--;
        }
        res.push_back(ch - '0');
    }
    while(k > 0)
    {
        res.pop_back();
        k--;
    }
    while(res.front() == 0 && !res.empty())
    {
        res.pop_front();
    }
    if(res.empty())
    {
        cout << 0;
        return 0;
    }
    // cout << k << "\n";
    for (auto i : res)
    {
        cout << i;
    }
    return 0;
}