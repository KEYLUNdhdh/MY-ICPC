#include <bits/stdc++.h>
using namespace std;
const int N = 3e4 + 5;
int main()
{
    int maxx, n;
    cin >> maxx >> n;
    deque<int> d(n);
    for (int i = 0; i < n;i++)
    {
        cin >> d[i];
    }
    sort(d.begin(), d.end());
    // deque<int> rest;
    int cnt = 0;
    while(d.size() > 1)
    {
        if (d.front() + d.back() <= maxx)
        {
            cnt++;
            d.pop_back();
            d.pop_front();
        }
        else
        {
            d.pop_back();
            cnt++;
        }
    }
    cnt += d.size();
    cout << cnt;
}