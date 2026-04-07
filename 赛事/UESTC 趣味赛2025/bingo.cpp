#include <bits/stdc++.h>
#define ld long double
using namespace std;
ld a[6][6];
typedef struct test{
    int id;
    int val = 0;
}kkk;
vector<kkk> exppp;
ld p;
bool comp(kkk k1,kkk k2)
{
    return k1.val <= k2.val;
}
void check(int tp)
{
    kkk temp;
    temp.id = tp;
    if(tp == 0)
    {
        if (a[0][0] == 1 &&a[1][0] == 1 && a[2][0] == 1 && a[3][0] == 1)
            temp.val++;
        if (a[0][4] == 1 &&a[1][3] == 1 && a[2][2] == 1 && a[3][1] == 1)
            temp.val++;
    }
    else if(tp == 1)
    {
        if(a[0][1] == 1 && a[1][1] == 1 && a[2][1] == 1 && a[3][1] == 1)
            temp.val++;
    }
    else if (tp == 2)
    {
        if (a[0][2] == 1 && a[1][2] == 1 && a[2][2] == 1 && a[3][2] == 1)
            temp.val++;
    }
    else if(tp == 3)
    {
        if(a[0][3] == 1 && a[1][3] == 1 && a[2][3] == 1 && a[3][3] == 1)
            temp.val++;
    }
    else if (tp == 4)
    {
        if (a[0][4] == 1 && a[1][4] == 1 && a[2][4] == 1 && a[3][4] == 1)
            temp.val++;
        if(a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 1 && a[3][3] == 1)
            temp.val++;
    }
    exppp.push_back(temp);
}
int main()
{
    for (int i = 0; i < 4;i++)
        for (int j = 0; j < 5;j++)
            cin >> a[i][j];
    cin >> p;
    ld grade = 0;
    for (int i = 0; i < 4;i++)
    {
        ld temp = 1;
        for (int j = 0; j < 5;j++)
        {
            temp *= a[i][j];
        }
        grade += temp;
    }
    for (int i = 0; i < 5;i++)
    {
        check(i);
    }
    sort(exppp.begin(), exppp.end(), comp);
    vector<kkk> temp;
    int tpval = exppp.rbegin()->val;
    for (auto it = exppp.rbegin(); it != exppp.rend();it++)
    {
        if(it->val == tpval)
        {
            temp.push_back(*it);
        }
        else
        {
            ld len = temp.size();
            ld tempp = min(p / len, (ld)1);
            for (auto i : temp)
            {
                a[4][i.id] = tempp;
            }
            p -= len * tempp;
            temp.clear();
            tpval = it->val;
            temp.push_back(*it);
        }
    }
    ld len = temp.size();
    ld tempp = min(p / len, (ld)1);
    for (auto i : temp)
    {
        a[4][i.id] = tempp;
    }
    grade += a[4][0] * a[4][1] * a[4][2] * a[4][3] * a[4][4];
    for (int j = 0; j < 5;j++)
    {
        ld temp = 1;
        for (int i = 0; i < 5;i++)
        {
            temp *= a[i][j];
        }
        grade += temp;
    }
    grade += a[0][0] * a[1][1] * a[2][2] * a[3][3] * a[4][4];
    grade += a[0][4] * a[1][3] * a[2][2] * a[3][1] * a[4][0];
    cout << fixed << setprecision(11) << grade;
}