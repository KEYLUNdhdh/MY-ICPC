#include <bits/stdc++.h>
using namespace std;
unordered_map<int, int> cnt;
string s,l,r;
int m;
void search(int pos)
{
    cnt.clear();
    for (int i = pos; i < s.size();i++)
        {
            if (cnt.count(s[i] - '0'))
                continue;
            else
            {
                cnt[s[i] - '0'] = i;
            }
            if(cnt.size() == 10)
                break;
        }
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> s >> m >> l >> r;
        search(0);
        int flag = 0;
        for (int i = 0; i < m;i++)
        {
            int left = l[i] - '0';
            int right = r[i] - '0';
            int suo = -1;
            for (int k = left; k <= right;k++)
            {
                if (!cnt.count(k))
                {
                    flag = 1;
                    break;
                }
                else
                {
                    suo = max(suo, cnt[k]);
                }
            }
            if (flag)
            {
                cout << "YES\n";
                break;
            }
            if (suo == -1)
            {
                cout << "YES\n";
                flag = 1;
                break;
            }
            else
            {
                search(suo + 1);
            }
        }
        if (flag)
            continue;
        else
            cout << "NO\n";
    }
}