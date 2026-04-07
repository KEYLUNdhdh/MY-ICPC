#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int dp[N] = {0};
int main()
{
    int t;
    cin >> t;
    string s;
    while(t--)
    {
        cin >> s;   
        if(s[0] == 'u')
        {
            dp[0] = 1;
        }
        else
        {
            dp[0] = 0;
        }
        dp[1] = (s[1] == 'u' ? 1 : 0) + dp[0];
        for (int i = 2; i < s.size();i++)
        {
            dp[i] = (s[i] == 'u' ? 1 : 0) + min(dp[i - 1], dp[i - 2]);
        }
        cout << dp[s.size() - 1] << "\n";
    }
    
}