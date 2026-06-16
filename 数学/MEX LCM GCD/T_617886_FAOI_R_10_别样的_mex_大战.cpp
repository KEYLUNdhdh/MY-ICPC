#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int a[N];
int n;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        int prefix = 0;
        //取mex就建立一个map直接作为vis数组
        map<int, int> mp;
        for (int i = 0; i < n;i++)
        {
            cin >> a[i];
            prefix ^= a[i];
            mp[a[i]]++;
        }
        int M = 0;
        while(mp[M])
            M++;
        if(prefix == M)
            cout << 0 << "\n\n";
        else 
        {
            if(prefix != 0)
            {
                cout << 1 << "\n";
                cout << (M ^ prefix) << "\n";
            }
            else
            {
                cout << 2 << "\n";
                int Mn = M + 1;
                while(mp[Mn])
                    Mn++;
                prefix = prefix ^ M;
                cout << M << " " << (Mn ^prefix) << "\n"; 
            }
        }
    }
} 