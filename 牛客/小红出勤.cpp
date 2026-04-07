#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, p, k;
map<string, int> mp;
// vector<string> st;
signed  main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    string s;
    int tp;
    while(t--)
    {

        cin >> n >> p >> k;
        int sumall = 0;
        for (int i = 0; i < n;i++)
        {
            cin >> s >> tp;
            mp[s] = tp;
            sumall += tp;
        }
        int minn_ci = 0x3f3f3f3f;
        for (int i = 0; i < k;i++)
        {
            cin >> s;
            minn_ci = min(minn_ci, mp[s]);
        }
        int minn = (sumall + p - 1) / p;
        int maxx = minn_ci;
        if(minn > maxx)
        {
            cout << "-1\n";
            continue;
        }
        else
        {
            cout << minn << " " << maxx << "\n";
        }
        mp.clear();
        // for (int i = 0; i < k;i++)
        // {
        //     cin >> s;
        //     st.push_back(s);
        // }
       
        // int sum_n = 0;
        // int sum_u = 0;
        // for(auto it : st)
        // {
        //     minn_ci = min(mp[it], minn_ci);
        //     sum_n += mp[it];
        // }
        // for(auto it : mp)
        // {
        //     sum_u += it.second;
        // }
        // sum_u -= sum_n;
        // if(minn_ci * p < sum_u + sum_n || p == st.size())
        // {
        //     cout << "-1\n";
        //     continue;
        // }
        // int playu = p - st.size();
        // int ci_u = (sum_u + playu - 1) / playu;
        // int sumciu = playu * ci_u;
        // int res = sumciu - sum_u;
        // sum_n -= res;
        // int ci_n = (sum_n + p - 1) / p;
        // cout << ci_n + ci_u  << " " << minn_ci << "\n";
        // st.clear();
        // mp.clear();
    }   
}