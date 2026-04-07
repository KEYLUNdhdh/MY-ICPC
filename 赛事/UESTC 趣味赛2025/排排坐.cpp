#include <bits/stdc++.h>
using namespace std;

int get_id(char c)
{
    if (c == 'U')
    {
        return 1;
    }
    if(c == 'E')
    {
        return 2;
    }
    if (c == 'S')
    {
        return 3;
    }
    return 0;
}

char get_char(int x)
{
    if (x == 1)
    {
        return 'U';
    }
    if(x== 2)
    {
        return 'E';
    }
    if (x == 3)
    {
        return 'S';
    }
    return ' ';
}



void solve()
{
    int n;
    cin >> n;
    int l, r;
    cin >> l >> r;
    string s;
    cin >> s;
    s = " " + s;
    s.append(" ");
    vector<int> cnt(4, 0);
    bool flag = true;
    for (int i = 1; i <= l - 1;i++)
    {
        if (s[i] == s[i - 1])  
        {
            flag = false;
        }
    }
    for (int i = r + 1; i <= n;i++)
    {
        if (s[i] == s[i  +1])
        {
            flag = false;
        }
    }
    auto check = [&](char c, char lc, char rc) -> bool
    {
        int sum = 0;
        int x = get_id(c);
        if (cnt[x] == 0)
        {
            return false;
        }
        cnt[x]--;
        for  (int i = 1; i <= 3;i++)
        {
            sum += cnt[i];
        }
        if (sum == 0)
        {
            return true;
        }
        //每个字符都检查一遍
        for (int i = 1; i <= 3;i++)
        {
            char t = get_char(i);
            if (t == lc && t == rc)
            {
                if (cnt[i] >(sum - 1) /2)
                {
                    cnt[x]++;
                    return false;
                }
            }
            else if(t == lc || t == rc)
            {
                if (cnt[i] > (sum) / 2)
                {
                    cnt[x]++;
                    return false;
                }
            }
            else
            {
                if (cnt[i] > (sum + 1) / 2)
                {
                    cnt[x]++;
                    return false;
                }
            }
        }
        return true;
    };
    for (int i = l; i <= r;i++)
    {
        cnt[get_id(s[i])]++;
    }
    cnt[get_id(s[l - 1])]++;
    if (!check(s[l - 1],s[l - 1],s[r + 1]))
    {
        flag = false;
    }
    if (!flag)
    {
        cout << -1 << "\n";
        return;
    }
    for (int i = l; i <= r;i++)
    {
        bool ok = false;
        for (int k = 1; k <= 3;k++)
        {
            char c = get_char(k);
            if (c== s[i -1])
            {
                continue;
            }
            if (check(c,c,s[r + 1]))
            {
                ok = true;
                s[i] = c;
                break;
            }
        }
        if (!ok)
        {
            cout << -1 << "\n";
            return;
        }
    }
    for (int i = 1; i <= n;i++)
    {
        cout << s[i];
    }
    cout << "\n";
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}