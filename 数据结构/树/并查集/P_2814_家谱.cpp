#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e4 + 5;
string name[MAXN];
int fa[MAXN];
vector<string> vec;
inline int Find(int x)
{
    if(fa[x] == x)
        return x;
    else
        return fa[x] = Find(fa[x]);
}

inline void merge(string father,string son)
{
    auto getid = [&](string s)
    {
        return lower_bound(vec.begin(), vec.end(), s) - vec.begin() + 1;
    };
    int ffa = Find(getid(father));
    int fson = Find(getid(son));
    if(ffa != fson)
        fa[fson] = ffa;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int index = 0;
    while(s[0] != '?')
    {
        name[index++] = s;
        vec.push_back(s.substr(1));
        cin >> s;
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (int i = 1; i <= vec.size();i++)
    {
        fa[i] = i;
    }
        string prev, now;
    for (int i = 0; i < index;i++)
    {
        if(name[i][0] == '#')
        {
            prev = name[i].substr(1);
            continue;
        }
        else
        {
            now = name[i].substr(1);
            merge(prev, now);
        }
    }
    auto getid = [&](string s)
    {
        return lower_bound(vec.begin(), vec.end(), s) - vec.begin() + 1;
    };
    string q = s.substr(1);
    int ans = Find(getid(q));
    cout << q << " " << vec[fa[ans] - 1] << "\n";
    cin >> s;
    while(s != "$")
    {
        string q = s.substr(1);
        int ans = Find(getid(q));
        cout << q << " " << vec[fa[ans] - 1] << "\n";
        cin >> s;
    }
}