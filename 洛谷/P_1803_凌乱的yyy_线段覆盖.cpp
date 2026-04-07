#include <bits/stdc++.h>
using namespace std;
typedef struct Segment{
    int l, r;
} seg;
bool comp(seg s1,seg s2)
{
    return s1.r < s2.r;
}
int main()
{
    vector<seg> vec;
    int n;
    cin >> n;
    seg temp;
    for (int i = 0; i < n;i++)
    {
        cin >> temp.l >> temp.r;
        vec.push_back(temp);
    }
    sort(vec.begin(), vec.end(), comp);
    vector<seg> ans;
    for(auto it : vec)
    {
        if(ans.empty())
        {
            ans.push_back(it);
        }
        else
        {
            if(ans.back().r <= it.l)
                ans.push_back(it);
        }
    }
    cout << ans.size();
}