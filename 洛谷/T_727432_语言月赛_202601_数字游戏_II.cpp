#include <bits/stdc++.h>
using namespace std;
int c[10][10];
vector<int> res[5][5];
vector<int> getj(vector<int>& v1,vector<int>& v2)
{
    vector<int> res;
    int a[5] = {0};
    for(auto i : v1)
    {
        a[i]++;
    }
    for(auto i : v2)
    {
        a[i]++;
    }
    for (int i = 1; i <= 4;i++)
    {
        if(a[i] == 0)
            res.push_back(i);
    }
    return res;
};
pair<int,int> remin()
{
    int minn = 10;
    int posi = -1, posj = -1;
    for (int i = 1; i <= 4;i++)
    {
        for (int j = 1; j <= 4;j++)
        {
            if(res[i][j].size() != 0 && res[i][j].size() < minn)
            {
                minn = res[i][j].size();
                posi = i;
                posj = j;
            }
        }
    }
    return {posi, posj};
}
int main()
{
    int cnt = 0;
    for (int i = 1; i <= 4;i++)
        for (int j = 1; j <= 4;j++)
        {
            cin >> c[i][j];
            if(c[i][j] == 0)
                cnt++;
        }
    vector<int> kong;
    for (int i = 1; i <= 4;i++)
    {
        for (int j = 1; j <= 4;j++)
        {
            if(c[i][j] != 0)
            {
                res[i][j] = kong;
                continue;
            }
            vector<int> v1,v2;
            for (int k = 1;k <= 4;k++)
            {
                if(c[i][k] != 0)
                    v1.push_back(c[i][k]);
            }
            for (int k = 1;k <= 4;k++)
            {
                if(c[k][j] != 0)
                    v2.push_back(c[k][j]);
            }
            res[i][j] = getj(v1, v2);
        }
    }
    while(cnt--)
    {
        auto p = remin();
        if(p.first == -1 || p.second == -1)
            break;
        int i = p.first;
        int j = p.second;
        int ans = res[i][j].back();
        c[i][j] = ans;
        res[i][j].clear();
        //gengxin
        for (int k = 1; k <= 4;k++)
        {
            if(c[i][k] == 0)
            {
                for (auto it = res[i][k].begin(); it != res[i][k].end();it++)
                {
                    if(*it == ans)
                    {
                        res[i][k].erase(it);
                        break;
                    }
                }
            }
        }
        for (int k = 1; k <= 4;k++)
        {
            if(c[k][j] == 0)
            {
                for (auto it = res[k][j].begin(); it != res[k][j].end();it++)
                {
                    if(*it == ans)
                    {
                        res[k][j].erase(it);
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= 4;i++)
    {
        for (int j = 1; j <= 4;j++)
        {
            cout << c[i][j];
            if(j != 4)
                cout << " ";
        }
        cout << "\n";
    }
}