#include <bits/stdc++.h>
using namespace std;
map<int, int> mp;
int main()
{
    int n;
    cin >> n;
    int val;
    for (int i = 0; i < n;i++)
    {
        cin >> val;
        mp[val]++;
    }
    int minn = 0x3f3f3f3f;
    // queue<queue<int>> q;
    deque<int> q;
    int lastval = -2e9;
    for (auto it : mp)
    {
        int nowval = it.first;
        int cnt = it.second;
        if(nowval != lastval + 1)
        {
            while(!q.empty())
            {
                minn = min(minn, lastval - q.front() + 1);
                q.pop_front();
            }
        }
        int neww = cnt - q.size();
        if (neww >= 0)
        {
            for (int i = 0;i < neww;i++)
            {
                q.push_back(nowval);
            }
        }
        else
        {
            neww = abs(neww);
            for (int i = 0; i < neww;i++)
            {
                minn = min(minn, lastval - q.front() + 1);
                q.pop_front();
            }
        }
        lastval = nowval;
    }
    while(!q.empty())
    {
        minn = min(minn, lastval - q.front() + 1);
        q.pop_front();
    }
    cout << minn;
}