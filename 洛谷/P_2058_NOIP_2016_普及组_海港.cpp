#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
typedef struct ship{
    int t, k = 0;
    vector<int> vec;
}ship;
set<int> all;
vector<ship> v;
int a[N];
int cnt = 0;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    ship tp;
    int temp;
    for (int i = 0; i < n;i++)
    {
        cin >> tp.t >> tp.k;
        for (int j = 0; j < tp.k;j++)
        {
            cin >> temp;
            tp.vec.push_back(temp);
        }
        v.push_back(tp);
        tp.vec.clear();
    }
    deque<ship> d;
    int index = 0;
    for (int i = 0; i < n;i++)
    {
        while(index < n &&v[index].t > v[i].t - 86400 && v[index].t <= v[i].t)
        {
            d.push_back(v[index]);
            for (int j = 0; j < d.back().vec.size();j++)
            {
                a[d.back().vec[j]]++;
                if(a[d.back().vec[j]] == 1)
                    cnt++;
            }
            index++;
        }
        while(!d.empty() && ((d.front().t <= v[i].t - 86400) || d.front().t > v[i].t))
        {
            for (int j = 0; j < d.front().vec.size();j++)
            {
                a[d.front().vec[j]]--;
                if(a[d.front().vec[j]] == 0)
                    cnt--;
            }
            d.pop_front();
        }
        cout << cnt << "\n";
    }
}   
