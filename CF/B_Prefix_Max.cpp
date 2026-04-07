#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    int n,tp,maxx =0;
    while(t--)
    {
        cin >> n;
        for (int i = 0; i < n;i++)
        {
            cin >> tp;
            maxx = max(tp, maxx);
        }
        cout << n * maxx << "\n";
        maxx = 0;
    }
}