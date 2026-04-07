#include <bits/stdc++.h>
using namespace std;
//贪心选择

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> vec;
        vec.push_back(-2);
        for (int i = 0; i < n;i++)
        {
            if(s[i] == '1')
            {
                vec.push_back(i);
            }
        }
        vec.push_back(n + 1);
        int ini = vec.size() - 2;
        for (int i = 0; i < vec.size() - 1;i++)
        {
            int g = vec[i + 1] - vec[i] - 1;
            ini += g / 3;
        }
        cout << ini << "\n";
    }
}