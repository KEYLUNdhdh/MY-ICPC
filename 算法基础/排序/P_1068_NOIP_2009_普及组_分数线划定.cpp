#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class cp
{
public:
    int id;
    int grade;
};
bool cop1(cp p, cp q) 
{
    return p.grade > q.grade;
}
bool cop2(cp p,cp q)
{
    if (p.grade == q.grade)
    {
        return p.id < q.id;
    }
    else
    {
        return p.grade > q.grade;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<cp> a;
    for (int i = 0; i < n;++i)
    {
        cp temp;
        cin >> temp.id >> temp.grade;
        a.push_back(temp);
    }
    sort(a.begin(), a.end(), cop1);
    int t = (double)m * 1.5 - 1;
    int gradet = a[t].grade;
    while (a[t].grade == gradet)
    {
        t++;
    }
    sort(a.begin(), a.end(), cop2);
    cout << gradet << " " << t << "\n";
    for (int i = 0; i < t;i++)
    {
        cout << a[i].id << " " << a[i].grade << "\n";
    }
}