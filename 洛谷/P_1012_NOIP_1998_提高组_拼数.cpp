#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define int long long
using namespace std;

bool cop(int a,int b)
{
    string s1 = to_string(a);
    string s2 = to_string(b);
    int max = s1.size() > s2.size() ? s2.size() : s1.size();
    string p1 = s1.substr(0, max);
    string p2 = s2.substr(0, max);
    if (p1 == p2)
    {
        if (s1.size() > s2.size())
        {
            return s2 < s1.substr(max, s1.size() - max);
        }
        else
        {
            return s1 > s2.substr(max, s2.size() - max);
        }
    }
    else
    {
        return s1 > s2;
    }
}
    signed main()
    {
        vector<int> a;
        int n;
        cin >> n;
        int temp;
        for (int i = 0; i < n; i++)
        {
            cin >> temp;
            a.push_back(temp);
        }
        sort(a.begin(), a.end(), cop);
        for (const auto &it : a)
        {
            cout << it;
        }
        return 0;
    }