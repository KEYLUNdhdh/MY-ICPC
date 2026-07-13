#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

vector<string> duval(const string &s)
{
    int n = s.length();
    int i = 0;
    vector<string> res;

    while(i < n)
    {
        int j = i + 1, k = i;
        while(j < n && s[j] >= s[k])
        {
            if(s[j] > s[k])
                k = i;
            else
                k++;
            j++;
        }

        while(i <= k)
        {
            res.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return res;
}