#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s;
int lim[500005] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    int dis;
    while (t--)
    {
        int cntu = 0, cnte = 0, cntc = 0, cnts = 0, cntt = 0;
        cin >> n >> s;
        s = " " + s;
        for (int i = 1; i <= n;i++)
            cin >> lim[i];
        for (int i = 1; i <= n;i++)
        {
            if (s[i] == 'U')
            {
                cntu += lim[i];
            }
            else if (s[i] == 'E')
            {
                dis = min(cntu, lim[i]);
                cnte += dis;
                cntu -= dis;
            }
            else if(s[i] == 'S')
            {
                dis = min(cnte, lim[i]);
                cnts += dis;
                cnte -= dis;
            }
            else if (s[i] == 'T')
            {
                dis = min(cnts, lim[i]);
                cntt += dis;
                cnts -= dis;
            }
            else
            {
                dis = min(cntt, lim[i]);
                cntt -= dis;
                cntc += dis;
            }
        }
        cout << cntc << "\n";
    }
}